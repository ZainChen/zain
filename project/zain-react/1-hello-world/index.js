document.addEventListener("DOMContentLoaded", ready);

function ready() {
    ZainReact.render('Hello World 0', document.getElementById('zian-react-content'));
    ZainReact.render('Hello World 1', document.getElementById('zian-react-content'));
    ZainReact.render(123456789, document.getElementById('zian-react-content'));
}

/**
 * zain react
 */
ZainReact = {
    // 即将创建的组件的 Id
    nextId: 0,
    // 渲染元素到指定元素内
    render: zainReactRender
}

/**
 * 渲染元素到指定元素内
 * @param {*} element 即将渲染的元素
 * @param {*} container 准备插入的目标元素
 */
function zainReactRender(element, container) {
    const zainComponentInstance = new ZainReactDOMTextComponent(element);
    const newElement = zainComponentInstance.createComponent(ZainReact.nextId++);
    container.appendChild(newElement);
}

/**
 * ZainReactDOMTextComponent 组件类
 * @param {*} text 这里只支持：typeof element === 'string' || typeof element === 'number'
 */
function ZainReactDOMTextComponent(text) {
    // 当前组件的元素内容
    this.element = text + '';
    // 当前组件 id
    this.id = null;
}

/**
 * 创建组件
 * @param {*} id 当前安装的组件 id
 */
ZainReactDOMTextComponent.prototype.createComponent = function(id) {
    this.id = id;
    const element = document.createElement('span');
    element.setAttribute('zain-react-id', id);
    element.innerText = this.element;
    return element;
}
