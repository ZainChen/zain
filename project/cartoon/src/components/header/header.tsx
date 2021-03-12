import './header.css';

export interface HeaderProps {
  children?: React.ReactNode;
}

export function Header(props: HeaderProps) {
  function handleStart() {
    console.log('zain>>>>>handleStart');
  }

  return (
    <div className="cartoon-header">
      cartoon header
      <button onClick={handleStart}>开始</button>
    </div>
  );
}
