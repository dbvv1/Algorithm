

// static ����
class Singleton {
public:
	// ��ȡ��������ĺ���
	static Singleton& getInstance()
	{
		static Singleton instance; // Guaranteed to be destroyed, instantiated on first use.
		return instance;
	}

	// ɾ�����ƹ��캯���͸�ֵ������
	Singleton(const Singleton&) = delete;             // Copy constructor
	Singleton& operator=(const Singleton&) = delete;  // Assignment operator

private:
	// �����캯��������������Ϊ˽�У���ֹ�ⲿ���������ٶ���
	Singleton() {}                                   // Constructor
	~Singleton() {}                                   // Destructor  
};