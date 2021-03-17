import { configureStore, ThunkAction, Action } from '@reduxjs/toolkit';
import { counterReducer } from 'src/store/counterStore';

export const store = configureStore({
    reducer: {
        counter: counterReducer,
    },
});

export type RootState = ReturnType<typeof store.getState>;
export type AppThunk<ReturnType = void> = ThunkAction<ReturnType, RootState, unknown, Action<string>>;
