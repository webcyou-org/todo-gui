const { createTaskElement } = require('../component/todoComponent')

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
                this.onToggleCompleted(todo);
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
        let isComposing = false;
        // Japanese input started
        this.input.addEventListener('compositionstart', () => {
            isComposing = true;
        });
        // Japanese input confirmed.
        this.input.addEventListener('compositionend', () => {
            isComposing = false;
        });

        this.input.addEventListener('keydown', event => {
            if (event.key === 'Enter' && !isComposing) {
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