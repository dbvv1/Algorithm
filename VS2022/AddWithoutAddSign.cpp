//���� + ʵ�� �ӷ�
int add(int a, int b) {
	while (b != 0) {
		int carry = (unsigned int)(a & b) << 1; // �����λ
		a = a ^ b; // �����޽�λ�ӷ����
		b = carry; // ����λ��ֵ��b������һ��ѭ������a���
	}
	return a;
}