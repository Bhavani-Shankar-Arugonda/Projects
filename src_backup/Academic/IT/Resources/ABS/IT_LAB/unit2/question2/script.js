document.addEventListener("DOMContentLoaded", function () {
    const taskInput = document.getElementById("taskInput");
    const dueDateInput = document.getElementById("dueDate");
    const addTaskBtn = document.getElementById("addTask");
    const taskList = document.getElementById("taskList");
    const filters = document.querySelectorAll(".filters button");

    let tasks = [];

    addTaskBtn.addEventListener("click", function () {
        const taskText = taskInput.value.trim();
        const dueDate = dueDateInput.value;
        if (taskText === "") return;

        const task = {
            text: taskText,
            dueDate: dueDate,
            completed: false
        };
        tasks.push(task);
        taskInput.value = "";
        dueDateInput.value = "";
        renderTasks();
    });

    function renderTasks(filter = "all") {
        taskList.innerHTML = "";
        const filteredTasks = tasks.filter(task => 
            filter === "all" || 
            (filter === "completed" && task.completed) || 
            (filter === "pending" && !task.completed)
        );
        
        filteredTasks.sort((a, b) => new Date(a.dueDate) - new Date(b.dueDate));

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
            renderTasks(this.dataset.filter);
        });
    });

    renderTasks();
});
