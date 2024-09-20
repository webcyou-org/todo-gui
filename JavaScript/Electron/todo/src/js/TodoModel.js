class Todo {
    constructor(data) {
        this.task = data.task ? data.task : "";
        this.isCompleted = data.isCompleted != null ? data.isCompleted : false;
    }
}

class TodoModel {
    constructor(todos) {
        this.list = [];
        todos.forEach((todo) => {
            this.list.push(new Todo(todo));
        })
    }

    getData() {
        return this.list;
    }

    addData(task) {
        this.list.push(new Todo({
            task
        }));
    }

    changeCompleted(index, isCompleted) {
        if (this.list[index]) {
            this.list[index].isCompleted = isCompleted;
        }
    }

    getFilteredTodos(tab) {
        if (tab.text === 'All') {
            return this.list;
        } else if (tab.text === 'Active') {
            return this.list.filter(todo => !todo.isCompleted);
        } else if (tab.text === 'Completed') {
            return this.list.filter(todo => todo.isCompleted);
        }
    }

    removeData(index) {
        this.list.splice(index, 1);
    }
}

module.exports = {
    TodoModel
};
