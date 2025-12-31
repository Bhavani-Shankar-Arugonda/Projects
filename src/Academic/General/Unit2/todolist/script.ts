document.addEventListener("DOMContentLoaded", function () {
    const taskInput = document.getElementById("taskInput") as HTMLInputElement;
    const dueDateInput = document.getElementById("dueDate") as HTMLInputElement;
    const addTaskBtn = document.getElementById("addTask") as HTMLButtonElement;
    const taskList = document.getElementById("taskList") as HTMLUListElement;
    const filters = document.querySelectorAll<HTMLButtonElement>(".filters button");

    interface Task {
        text: string;
        dueDate: string;
        completed: boolean;
    }

    let tasks: Task[] = [];

    addTaskBtn.addEventListener("click", function () {
        const taskText = taskInput.value.trim();
        const dueDate = dueDateInput.value;
        if (taskText === "") return;

        const task: Task = {
            text: taskText,
            dueDate: dueDate,
            completed: false
        };
        tasks.push(task);
        taskInput.value = "";
        dueDateInput.value = "";
        renderTasks();
    });

    function renderTasks(filter: string = "all"): void {
        taskList.innerHTML = "";
        const filteredTasks = tasks.filter(task => 
            filter === "all" || 
            (filter === "completed" && task.completed) || 
            (filter === "pending" && !task.completed)
        );
        
        filteredTasks.sort((a, b) => new Date(a.dueDate).getTime() - new Date(b.dueDate).getTime());

        filteredTasks.forEach((task, index) => {
            const li = document.createElement("li");
            li.textContent = `${task.text} (Due: ${task.dueDate})`;
            if (task.completed) li.classList.add("completed");
            
            li.addEventListener("click", function () {
                tasks[index].completed = !tasks[index].completed;
                renderTasks(filter);
            });
            taskList.appendChild(li);
        });
    }

    filters.forEach(button => {
        button.addEventListener("click", function () {
            renderTasks(this.dataset.filter!);
        });
    });

    renderTasks();
});
