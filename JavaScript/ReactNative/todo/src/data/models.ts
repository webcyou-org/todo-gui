import type {TabMenu, Todo} from './types';

export class TodoModel {
  private list: Todo[] = [
    {id: 1, task: 'Task1', isCompleted: false},
    {id: 2, task: 'Task2', isCompleted: true},
    {id: 3, task: 'Task3', isCompleted: false},
    {id: 4, task: 'Task4', isCompleted: false},
  ];
  private nextId = 5;

  getData(): Todo[] {
    return [...this.list];
  }

  addTodo(task: string): void {
    this.list.push({id: this.nextId++, task, isCompleted: false});
  }

  findById(id: number): Todo | undefined {
    return this.list.find(t => t.id === id);
  }

  changeCompleted(todo: Todo): void {
    const t = this.list.find(t => t.id === todo.id);
    if (t) {
      t.isCompleted = !t.isCompleted;
    }
  }

  getFilteredTodos(tab: TabMenu): Todo[] {
    switch (tab.text) {
      case 'Active':
        return this.list.filter(t => !t.isCompleted);
      case 'Completed':
        return this.list.filter(t => t.isCompleted);
      default:
        return [...this.list];
    }
  }

  removeData(id: number): void {
    this.list = this.list.filter(t => t.id !== id);
  }
}

export class MenuModel {
  private tabList: TabMenu[] = [
    {text: 'All', isActive: true},
    {text: 'Active', isActive: false},
    {text: 'Completed', isActive: false},
  ];

  getTabList(): TabMenu[] {
    return [...this.tabList];
  }

  getActiveTab(): TabMenu {
    return this.tabList.find(t => t.isActive) ?? this.tabList[0];
  }

  setActiveTab(tabItem: TabMenu): void {
    this.tabList = this.tabList.map(t => ({
      ...t,
      isActive: t.text === tabItem.text,
    }));
  }
}
