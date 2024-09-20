const { createTaskElement } = require('./component/todoComponent')

class TodoView {
    constructor() {
        this.input = document.getElementById('todoInput');
        this.list = document.getElementById('todoList');
    }

    renderList(todos) {
        this.list.innerHTML = '';
        todos.forEach((todo, index) => {
            const li = createTaskElement(todo);
            this.list.appendChild(li);
            li.addEventListener('click', () => {
                this.onToggleCompleted(index);
            });
        });
    }

    getInputValue() {
        return this.input.value;
    }

    clearInput() {
        this.input.value = '';
    }

    bindAddItem(handler) {
        this.input.addEventListener('keydown', event => {
            if (event.key === 'Enter') {
                event.preventDefault();
                handler(this.getInputValue());
                this.clearInput();
            }
        });
    }

    bindToggleCompleted(handler) {
        this.onToggleCompleted = handler;
    }
}

module.exports = {
    TodoView
};