import tensorflow as tf
from tensorflow.keras.layers import Conv2D, BatchNormalization, ReLU, MaxPooling2D
from tensorflow.keras.layers import GlobalAveragePooling2D, Dense, Add, Input
from tensorflow.keras import Model
from typing import Tuple, Optional


class ResidualBlock(tf.keras.layers.Layer):
    def __init__(self, filters: int, kernel_size: int = 3, stride: int = 1, 
                 use_skip_conv: bool = False):
        """
        Базовый остаточный блок (2 сверточных слоя)
        
        Args:
            filters: Количество фильтров в сверточных слоях
            kernel_size: Размер ядра свертки
            stride: Шаг свертки
            use_skip_conv: Использовать ли дополнительную свертку для skip connection
        """
        super(ResidualBlock, self).__init__()
        
        self.filters = filters
        self.stride = stride
        self.use_skip_conv = use_skip_conv
        
        # Основной путь
        self.conv1 = Conv2D(filters, kernel_size, stride, padding='same',
                           kernel_initializer='he_normal')
        self.bn1 = BatchNormalization()
        
        self.conv2 = Conv2D(filters, kernel_size, 1, padding='same',
                           kernel_initializer='he_normal')
        self.bn2 = BatchNormalization()
        
        # Skip connection путь (если нужно изменить размерность)
        if use_skip_conv:
            self.skip_conv = Conv2D(filters, 1, stride, padding='same',
                                   kernel_initializer='he_normal')
            self.skip_bn = BatchNormalization()
        
        self.relu = ReLU()
    
    def build(self, input_shape):
        # Автоматически определяем, нужна ли skip connection
        if input_shape[-1] != self.filters or self.stride > 1:
            self.use_skip_conv = True
            if not hasattr(self, 'skip_conv'):
                self.skip_conv = Conv2D(self.filters, 1, self.stride, padding='same',
                                       kernel_initializer='he_normal')
                self.skip_bn = BatchNormalization()
        super().build(input_shape)
    
    def call(self, x: tf.Tensor, training: bool = False) -> tf.Tensor:
        identity = x
        
        # Основной путь
        x = self.conv1(x)
        x = self.bn1(x, training=training)
        x = self.relu(x)
        
        x = self.conv2(x)
        x = self.bn2(x, training=training)
        
        # Skip connection
        if self.use_skip_conv:
            identity = self.skip_conv(identity)
            identity = self.skip_bn(identity, training=training)
        
        # Сложение и активация
        x = Add()([x, identity])
        x = self.relu(x)
        
        return x


class BottleneckBlock(tf.keras.layers.Layer):
    def __init__(self, filters: int, stride: int = 1,
                 use_skip_conv: bool = False):
        """
        Bottleneck блок (1x1 -> 3x3 -> 1x1 свертки)
        
        Args:
            filters: Количество фильтров в выходном слое
            stride: Шаг свертки
            use_skip_conv: Использовать ли дополнительную свертку для skip connection
        """
        super(BottleneckBlock, self).__init__()
        
        self.filters = filters
        self.stride = stride
        self.use_skip_conv = use_skip_conv
        
        # Путь сжатия (уменьшение размерности)
        self.conv1 = Conv2D(filters // 4, 1, stride, padding='same',
                           kernel_initializer='he_normal')
        self.bn1 = BatchNormalization()
        
        # Основной сверточный слой
        self.conv2 = Conv2D(filters // 4, 3, 1, padding='same',
                           kernel_initializer='he_normal')
        self.bn2 = BatchNormalization()
        
        # Путь расширения (возврат к исходной размерности)
        self.conv3 = Conv2D(filters, 1, 1, padding='same',
                           kernel_initializer='he_normal')
        self.bn3 = BatchNormalization()
        
        # Skip connection путь
        if use_skip_conv:
            self.skip_conv = Conv2D(filters, 1, stride, padding='same',
                                   kernel_initializer='he_normal')
            self.skip_bn = BatchNormalization()
        
        self.relu = ReLU()
    
    def build(self, input_shape):
        # Автоматически определяем, нужна ли skip connection
        if input_shape[-1] != self.filters or self.stride > 1:
            self.use_skip_conv = True
            if not hasattr(self, 'skip_conv'):
                self.skip_conv = Conv2D(self.filters, 1, self.stride, padding='same',
                                       kernel_initializer='he_normal')
                self.skip_bn = BatchNormalization()
        super().build(input_shape)
    
    def call(self, x: tf.Tensor, training: bool = False) -> tf.Tensor:
        identity = x
        
        # Основной путь
        x = self.conv1(x)
        x = self.bn1(x, training=training)
        x = self.relu(x)
        
        x = self.conv2(x)
        x = self.bn2(x, training=training)
        x = self.relu(x)
        
        x = self.conv3(x)
        x = self.bn3(x, training=training)
        
        # Skip connection
        if self.use_skip_conv:
            identity = self.skip_conv(identity)
            identity = self.skip_bn(identity, training=training)
        
        # Сложение и активация
        x = Add()([x, identity])
        x = self.relu(x)
        
        return x


class ResNet50:
    def __init__(self, num_classes: int = 1000, input_shape: Tuple[int, int, int] = (224, 224, 3)):
        """
        Реализация ResNet-50 архитектуры
        
        Args:
            num_classes: Количество классов для классификации
            input_shape: Размер входного изображения
        """
        self.num_classes = num_classes
        self.input_shape = input_shape
        self.model = self._build_model()
    
    def _make_stage(self, x: tf.Tensor, filters: int, num_blocks: int, 
                   stride: int = 2, is_first_stage: bool = False) -> tf.Tensor:
        """
        Создание стадии ResNet (группы блоков)
        
        Args:
            x: Входной тензор
            filters: Количество фильтров
            num_blocks: Количество блоков в стадии
            stride: Шаг для первого блока
            is_first_stage: Первая ли это стадия
        """
        # Для первой стадии не используем stride, так как уже есть MaxPooling
        if is_first_stage:
            stride = 1
        
        # Первый блок в стадии может изменять размерность
        x = BottleneckBlock(filters, stride, use_skip_conv=True)(x)
        
        # Остальные блоки
        for _ in range(1, num_blocks):
            x = BottleneckBlock(filters, stride=1)(x)
        
        return x
    
    def _build_model(self) -> Model:
        """Построение полной модели ResNet-50"""
        
        # Входной слой
        inputs = Input(shape=self.input_shape)
        x = inputs
        
        # Начальные слои
        x = Conv2D(64, 7, strides=2, padding='same', 
                  kernel_initializer='he_normal')(x)
        x = BatchNormalization()(x)
        x = ReLU()(x)
        x = MaxPooling2D(pool_size=3, strides=2, padding='same')(x)
        
        # Стадия 1: 3 bottleneck блока с 256 фильтрами (64 * 4)
        x = self._make_stage(x, 256, 3, is_first_stage=True)
        
        # Стадия 2: 4 bottleneck блока с 512 фильтрами (128 * 4)
        x = self._make_stage(x, 512, 4)
        
        # Стадия 3: 6 bottleneck блоков с 1024 фильтрами (256 * 4)
        x = self._make_stage(x, 1024, 6)
        
        # Стадия 4: 3 bottleneck блока с 2048 фильтрами (512 * 4)
        x = self._make_stage(x, 2048, 3)
        
        # Финальные слои
        x = GlobalAveragePooling2D()(x)
        outputs = Dense(self.num_classes, activation='softmax',
                       kernel_initializer='he_normal')(x)
        
        # Создание модели
        model = Model(inputs=inputs, outputs=outputs, name='ResNet50')
        
        return model
    
    def compile(self, **kwargs):
        """Компиляция модели"""
        self.model.compile(**kwargs)
    
    def summary(self):
        """Вывод архитектуры модели"""
        return self.model.summary()
    
    def build_model(self, input_shape: Optional[Tuple[int, int, int]] = None):
        """
        Публичный метод для построения модели
        
        Args:
            input_shape: Размер входного изображения (необязательно)
        """
        if input_shape:
            self.input_shape = input_shape
        self.model = self._build_model()
        return self.model


# Пример использования
if __name__ == "__main__":
    # Создание модели
    resnet = ResNet50(num_classes=1000, input_shape=(224, 224, 3))
    
    # Вывод архитектуры
    resnet.summary()
    
    # Пример компиляции
    resnet.compile(
        optimizer='adam',
        loss='categorical_crossentropy',
        metrics=['accuracy']
    )
    
    # Пример использования ResidualBlock (не для ResNet-50, но для демонстрации)
    print("\nПример ResidualBlock:")
    inputs = Input(shape=(56, 56, 64))
    x = ResidualBlock(128, stride=2)(inputs)
    model = Model(inputs=inputs, outputs=x)
    model.summary()
    
    print("\nПример BottleneckBlock:")
    inputs = Input(shape=(56, 56, 256))
    x = BottleneckBlock(512, stride=2)(inputs)
    model = Model(inputs=inputs, outputs=x)
    model.summary()