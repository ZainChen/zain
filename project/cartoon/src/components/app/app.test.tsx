import React from 'react';
import { render } from '@testing-library/react';
import { Provider } from 'react-redux';
import { App } from 'src/components/app';
import { store } from 'src/store';

test('renders learn react link', () => {
    const { getByText } = render(
        <Provider store={store}>
            <App />
        </Provider>
    );

    expect(getByText(/learn/i)).toBeInTheDocument();
});
