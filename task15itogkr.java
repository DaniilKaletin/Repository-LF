import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class BinPacking {
    public static int firstFit(int[] weights, int W) {
        List<Integer> bins = new ArrayList<>(); // текущие загрузки контейнеров
        for (int w : weights) {
            boolean packed = false;
            for (int i = 0; i < bins.size(); i++) {
                if (bins.get(i) + w <= W) {
                    bins.set(i, bins.get(i) + w);
                    packed = true;
                    break;
                }
            }
            if (!packed) {
                // ДОПИСАНО: добавить новый контейнер с весом w
                bins.add(w);
            }
        }
        return bins.size();
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Ввод вместимости контейнера
        System.out.print("Введите вместимость контейнера W: ");
        int W = scanner.nextInt();
        
        // Ввод количества предметов
        System.out.print("Введите количество предметов: ");
        int n = scanner.nextInt();
        
        // Ввод весов предметов
        int[] weights = new int[n];
        System.out.println("Введите веса предметов:");
        for (int i = 0; i < n; i++) {
            System.out.print("Вес предмета " + (i + 1) + ": ");
            weights[i] = scanner.nextInt();
        }
        
        // Вычисление результата
        int result = firstFit(weights, W);
        
        // Вывод результата
        System.out.println("\nМаксимальное количество контейнеров: " + result);
        
        scanner.close();
    }
}
//Введите вместимость контейнера W: 10
//Введите количество предметов: 5
//Введите веса предметов:
//Вес предмета 1: 4
//Вес предмета 2: 7
//Вес предмета 3: 3
//Вес предмета 4: 5
//Вес предмета 5: 2
//Максимальное количество контейнеров: 3