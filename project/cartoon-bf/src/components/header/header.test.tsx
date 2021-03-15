import React from "react";
import { render, screen } from "@testing-library/react";
import { Header } from ".";

test("renders learn react link", () => {
    render(<Header />);
    const linkElement = screen.getByText(/header/i);
    expect(linkElement).toBeInTheDocument();
});
