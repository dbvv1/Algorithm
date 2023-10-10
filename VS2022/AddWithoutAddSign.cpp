//不用 + 实现 加法
int add(int a, int b) {
	while (b != 0) {
		int carry = (unsigned int)(a & b) << 1; // 计算进位
		a = a ^ b; // 计算无进位加法结果
		b = carry; // 将进位赋值给b，在下一次循环中与a相加
	}
	return a;
}