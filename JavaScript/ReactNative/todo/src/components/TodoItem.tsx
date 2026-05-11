import type React from 'react';
import {StyleSheet, Text, TouchableOpacity, View} from 'react-native';
import type {Todo} from '../data/types';
import {C, S, T} from '../theme';

interface Props {
  todo: Todo;
  onToggle: (todo: Todo) => void;
}

export function TodoItem({todo, onToggle}: Props): React.JSX.Element {
  return (
    <View style={styles.container}>
      <TouchableOpacity
        style={[styles.checkbox, todo.isCompleted && styles.checkboxChecked]}
        onPress={() => onToggle(todo)}
        activeOpacity={0.7}
      />
      <Text
        style={[styles.taskText, todo.isCompleted && styles.taskTextCompleted]}>
        {todo.task}
      </Text>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flexDirection: 'row',
    alignItems: 'center',
    height: S.ITEM_HEIGHT,
    backgroundColor: C.SURFACE,
    borderRadius: S.ITEM_RADIUS,
    paddingHorizontal: S.ITEM_PADDING,
    marginBottom: S.ITEM_MB,
  },
  checkbox: {
    width: S.CB_SIZE,
    height: S.CB_SIZE,
    borderRadius: S.CB_RADIUS,
    borderWidth: 2,
    borderColor: C.CB_BORDER,
    marginRight: S.CB_MR,
  },
  checkboxChecked: {
    backgroundColor: C.ACCENT,
    borderColor: C.ACCENT,
  },
  taskText: {
    color: C.TEXT,
    fontSize: T.FONT_SIZE_NORMAL,
    flex: 1,
  },
  taskTextCompleted: {
    textDecorationLine: 'line-through',
    color: C.MUTED,
  },
});
