def input_tasks():
    print('Введите данные в формате: 1 3, 2 5, 4 6')
    user_input = input().strip()
    
    if not user_input:
        return []
    
    tasks = []
    pairs = user_input.split(',')
    
    for pair in pairs:
        pair = pair.strip()
        if pair:
            numbers = pair.split()
            if len(numbers) == 2:
                try:
                    start, end = int(numbers[0]), int(numbers[1])
                    if start < end and start >= 0 and end >= 0:
                        tasks.append((start, end))
                except ValueError:
                    continue
    
    return tasks

def select_max_tasks(tasks):
    if not tasks:
        return [], 0
    
    sorted_tasks = sorted(tasks, key=lambda x: x[1])
    selected_tasks = []
    last_end_time = -1
    
    for task in sorted_tasks:
        start, end = task
        if start >= last_end_time:
            selected_tasks.append(task)
            last_end_time = end
    
    return selected_tasks, len(selected_tasks)

def main():
    tasks = input_tasks()
    
    if not tasks:
        print("Нет задач для обработки")
        return
    
    selected_tasks, count = select_max_tasks(tasks)
    
    print("\nВывод:")
    for task in selected_tasks:
        print(task)

if __name__ == "__main__":
    main()

#Вывод:
#(1,3)
#(4,6)
#(7,9)