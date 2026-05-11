export interface Todo {
  id: number;
  task: string;
  isCompleted: boolean;
}

export type TabText = 'All' | 'Active' | 'Completed';

export interface TabMenu {
  text: TabText;
  isActive: boolean;
}
