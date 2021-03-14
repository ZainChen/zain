import React from "react";
import "./header.scss";

export interface HeaderProps {
    children?: React.ReactNode;
}

export function Header(props: HeaderProps) {
    function handleStart() {
        console.log("zain>>>>>handleStart");
    }

    return (
        <div className="cartoon-header">
            cartoon header 漫画爬取工具
            <button onClick={handleStart}>开始</button>
        </div>
    );
}
