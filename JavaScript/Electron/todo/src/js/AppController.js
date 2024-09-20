const { TodoModel } = require('./Model/TodoModel');
const { MenuModel } = require('./Model/MenuModel');
const { TodoView } = require('./View/TodoView');
const { MenuView } = require('./View/MenuView');

class AppController {
    constructor(todoModel, todoView, menuModel, menuView) {
        this.todoModel = todoModel;
        this.todoView = todoView;
        this.menuModel = menuModel;
        this.menuView = menuView;

        // Initial rendering
        this.todoView.renderList(this.todoModel.getData());
        this.menuView.renderTabList(this.menuModel.getTabList());

        // Bind the view's event handlers
        this.todoView.bindAddItem(this.handleAddItem.bind(this));
        this.todoView.bindToggleCompleted(this.handleToggleCompleted.bind(this));
        this.menuView.bindTabClick(this.handleTabClick.bind(this));
    }

    handleAddItem(task) {
        this.todoModel.addData(task);
        this.updateTodoView();
    }

    handleToggleCompleted(index) {
        const currentTodo = this.todoModel.getData()[index];
        this.todoModel.changeCompleted(index, !currentTodo.isCompleted);
        this.updateTodoView();
    }

    handleTabClick(tab) {
        this.menuModel.setActiveTab(tab);
        this.updateTodoView();
        this.menuView.renderTabList(this.menuModel.getTabList());
    }

    updateTodoView() {
        this.todoView.renderList(this.todoModel.getFilteredTodos(this.menuModel.getActiveTab()));
    }
}

function initTodoApp(data) {
    return new AppController(
        new TodoModel(data),
        new TodoView(),
        new MenuModel(),
        new MenuView()
    );
}

module.exports = {
    AppController,
    initTodoApp
};