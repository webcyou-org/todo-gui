import type React from 'react';
import {ScrollView, StyleSheet} from 'react-native';
import type {Todo} from '../data/types';
import {TodoItem} from './TodoItem';

interface Props {
  todos: Todo[];
  onToggle: (todo: Todo) => void;
}

export function TodoList({todos, onToggle}: Props): React.JSX.Element {
  return (
    <ScrollView style={styles.container} showsVerticalScrollIndicator={false}>
      {todos.map(todo => (
        <TodoItem key={todo.id} todo={todo} onToggle={onToggle} />
      ))}
    </ScrollView>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
  },
});
