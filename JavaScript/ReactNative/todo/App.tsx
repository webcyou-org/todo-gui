import type React from 'react';
import {useState} from 'react';
import {SafeAreaView, StyleSheet, Text} from 'react-native';
import {TabMenu as TabMenuBar} from './src/components/TabMenu';
import {TodoInput} from './src/components/TodoInput';
import {TodoList} from './src/components/TodoList';
import {MenuModel, TodoModel} from './src/data/models';
import type {TabMenu, Todo} from './src/data/types';
import {C, S, T} from './src/theme';

const todoModel = new TodoModel();
const menuModel = new MenuModel();

function App(): React.JSX.Element {
  const [, setRevision] = useState(0);
  const [tabs, setTabs] = useState<TabMenu[]>(menuModel.getTabList());

  const refresh = () => setRevision(r => r + 1);
  const activeTab = tabs.find(t => t.isActive) ?? tabs[0];
  const filteredTodos = todoModel.getFilteredTodos(activeTab);

  const handleAddTodo = (task: string) => {
    todoModel.addTodo(task);
    refresh();
  };

  const handleToggle = (todo: Todo) => {
    todoModel.changeCompleted(todo);
    refresh();
  };

  const handleChangeTab = (tab: TabMenu) => {
    menuModel.setActiveTab(tab);
    setTabs(menuModel.getTabList());
  };

  return (
    <SafeAreaView style={styles.root}>
      <Text style={styles.title}>ToDo</Text>
      <TodoInput onAddTodo={handleAddTodo} />
      <TabMenuBar tabs={tabs} onChangeTab={handleChangeTab} />
      <TodoList todos={filteredTodos} onToggle={handleToggle} />
    </SafeAreaView>
  );
}

const styles = StyleSheet.create({
  root: {
    flex: 1,
    backgroundColor: C.BG,
    paddingHorizontal: S.CONTENT_H,
    paddingVertical: S.CONTENT_V,
  },
  title: {
    color: C.WHITE,
    fontSize: T.FONT_SIZE_TITLE,
    fontWeight: 'bold',
    marginBottom: S.TITLE_MB,
  },
});

export default App;
