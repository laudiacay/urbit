import f from 'lodash/fp';
import { RemoteContentPolicy, LeapCategories, leapCategories } from "~/types/local-update";
import { BaseState, createState } from '~/logic/state/base';


export interface SettingsState extends BaseState<SettingsState> {
  display: {
    backgroundType: 'none' | 'url' | 'color';
    background?: string;
    dark: boolean;
  };
  calm: {
    hideNicknames: boolean;
    hideAvatars: boolean;
    hideUnreads: boolean;
    hideGroups: boolean;
    hideUtilities: boolean;
  };
  remoteContentPolicy: RemoteContentPolicy;
  leap: {
    categories: LeapCategories[];
  }
};

export const selectSettingsState =
<K extends keyof SettingsState>(keys: K[]) => f.pick<SettingsState, K>(keys);

export const selectCalmState = (s: SettingsState) => s.calm;

const useSettingsState = createState<SettingsState>('Settings', {
  display: {
    backgroundType: 'none',
    background: undefined,
    dark: false,
  },
  calm: {
    hideNicknames: false,
    hideAvatars: false,
    hideUnreads: false,
    hideGroups: false,
    hideUtilities: false
  },
  remoteContentPolicy: {
    imageShown: true,
    oembedShown: true,
    audioShown: true,
    videoShown: true
  },
  leap: {
    categories: leapCategories,
  },
});

export default useSettingsState;