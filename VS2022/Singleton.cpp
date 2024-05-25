

// static 单例
class Singleton {
public:
	// 获取单例对象的函数
	static Singleton& getInstance()
	{
		static Singleton instance; // Guaranteed to be destroyed, instantiated on first use.
		return instance;
	}

	// 删除复制构造函数和赋值操作符
	Singleton(const Singleton&) = delete;             // Copy constructor
	Singleton& operator=(const Singleton&) = delete;  // Assignment operator

private:
	// 将构造函数和析构函数设为私有，防止外部创建或销毁对象
	Singleton() {}                                   // Constructor
	~Singleton() {}                                   // Destructor  
};