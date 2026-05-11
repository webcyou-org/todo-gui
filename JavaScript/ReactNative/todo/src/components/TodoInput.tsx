import type React from 'react';
import {useRef, useState} from 'react';
import {StyleSheet, TextInput, View} from 'react-native';
import {C, S} from '../theme';

interface Props {
  onAddTodo: (task: string) => void;
}

export function TodoInput({onAddTodo}: Props): React.JSX.Element {
  const [value, setValue] = useState('');
  const [focused, setFocused] = useState(false);
  const inputRef = useRef<TextInput>(null);

  const handleSubmit = () => {
    const trimmed = value.trim();
    if (trimmed) {
      onAddTodo(trimmed);
      setValue('');
    }
  };

  return (
    <View
      style={[
        styles.container,
        focused ? styles.containerFocused : styles.containerBlurred,
      ]}>
      <TextInput
        ref={inputRef}
        style={styles.input}
        value={value}
        onChangeText={setValue}
        placeholder="Add Task"
        placeholderTextColor={C.MUTED}
        onSubmitEditing={handleSubmit}
        blurOnSubmit={false}
        onFocus={() => setFocused(true)}
        onBlur={() => setFocused(false)}
        returnKeyType="done"
      />
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    height: S.INPUT_HEIGHT,
    backgroundColor: C.INPUT,
    borderRadius: S.ITEM_RADIUS,
    borderWidth: 1,
    marginBottom: S.INPUT_MB,
    justifyContent: 'center',
  },
  containerBlurred: {
    borderColor: 'transparent',
  },
  containerFocused: {
    borderColor: C.ACCENT,
  },
  input: {
    flex: 1,
    color: C.WHITE,
    fontSize: 14,
    paddingHorizontal: S.INPUT_PH,
    paddingVertical: S.INPUT_PV,
  },
});
