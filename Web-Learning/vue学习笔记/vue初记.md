
### vue标签
1. `v-text`
2. `v-html`
3. `v-on`：绑定事件
```vue
var app = new Vue({
el: "#app",
methods:{
doIt:function(){
//逻辑
  }
}
})
```
关于`vue`的一些特性：
v-on是绑定事，件简写为@，v-html是可以显示标签，v-text只会显示文本信息，el是挂载点，数据放在data区，方法放在methods区
v-show是检查表达式的值，根据表达式的值改变状态 v-if操作的是dom树， v-show标签操作的是样式
v-for语法为 {item, index} in 数据
v-model作用是便捷地设置和获取表单内容，绑定数据和表单元素相关联