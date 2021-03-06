# 数位dp

1. 数位dp的形式貌似是模板化的。
2. 数位dp一般解决的问题是求出`[A,B]` 区间的满足条件`f(i)`的数i的个数
3. 对于区间`[A, B]`的满足方案数一般通过`[0, B]` 来解决



#### 记忆化搜索

dfs函数需要的量：

- 基本的量：数字的位数`pos`，记录答案的`st`，最高位限制`limit`
- 还需要一个判断前导零的标记`lead`
- 数位dp的dp值常需要用到记录前一位或前几位的状态值，所以dfs中常需要记录其与前一位或前几位的值pre方便比较
- dp的下标记录的是某个数的状态值，一旦当前的状态值与之前已经搜索过的状态值相同，则可以直接返回之前已经记录下来的状态值