const { TAB_MENU_TEXT } = require('../const/tabMenuData')
const { defaultTodoData } = require('../const/todoData')

class Todo {
    constructor(data, index) {
        this.id = index ? index : 0;
        this.task = data.task ? data.task : "";
        this.isCompleted = data.isCompleted != null ? data.isCompleted : false;
    }
}

class TodoModel {
    constructor(todos = defaultTodoData) {
        this.list = [];
        todos.forEach((todo, index) => {
            this.list.push(new Todo(todo, index + 1));
        })
    }

    getData() {
        return this.list;
    }

    addData(task) {
        this.list.push(
            new Todo({
                    task
                },
                this.list.length + 1
            )
        );
    }

    findById(id) {
        return this.list.find(todo => todo.id === id)
    }

    changeCompleted(todo) {
        let targetTodo = this.findById(todo.id)
        if (targetTodo) {
            targetTodo.isCompleted = !targetTodo.isCompleted;
        }
    }

    getFilteredTodos(tab) {
        switch (tab.text) {
            case TAB_MENU_TEXT.ALL:
                return this.list;
            case TAB_MENU_TEXT.ACTIVE:
                return this.list.filter(todo => !todo.isCompleted);
            case TAB_MENU_TEXT.COMPLETED:
                return this.list.filter(todo => todo.isCompleted);
            default:
                return this.list;
        }
    }

    removeData(id) {
        const index = this.list.findIndex(todo => todo.id === id);
        if (index !== -1) {
            this.list.splice(index, 1);
        } else {
            console.log("Todo not found");
        }
    }
}

module.exports = {
    TodoModel
};
