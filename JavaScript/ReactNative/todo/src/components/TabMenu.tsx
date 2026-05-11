import type React from 'react';
import {StyleSheet, Text, TouchableOpacity, View} from 'react-native';
import type {TabMenu as TabMenuType} from '../data/types';
import {C, S, T} from '../theme';

interface Props {
  tabs: TabMenuType[];
  onChangeTab: (tab: TabMenuType) => void;
}

export function TabMenu({tabs, onChangeTab}: Props): React.JSX.Element {
  return (
    <View style={styles.container}>
      {tabs.map(tab => (
        <TouchableOpacity
          key={tab.text}
          onPress={() => onChangeTab(tab)}
          style={styles.tabItem}>
          <Text style={[styles.tabText, tab.isActive && styles.tabTextActive]}>
            {tab.text}
          </Text>
        </TouchableOpacity>
      ))}
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flexDirection: 'row',
    marginBottom: S.TAB_MB,
  },
  tabItem: {
    paddingHorizontal: S.TAB_ITEM_PH,
  },
  tabText: {
    color: C.TEXT,
    fontSize: T.FONT_SIZE_NORMAL,
    lineHeight: S.TAB_LINE_HEIGHT,
    fontWeight: 'normal',
  },
  tabTextActive: {
    fontWeight: 'bold',
  },
});
