template <typename T>
class unique_ptr 
{
public:
    explicit unique_ptr(T* ptr = nullptr) : m_ptr(ptr) {}

    ~unique_ptr() { delete m_ptr; }


    unique_ptr(unique_ptr&& other) noexcept : m_ptr(other.release()) {}

    unique_ptr& operator=(unique_ptr&& other)  noexcept
    {
        reset(other.release());
        return *this;
    }

    //删除拷贝语义
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;


    T* release() 
    {
        T* ptr = m_ptr;
        m_ptr = nullptr;
        return ptr;
    }

    void reset(T* ptr = nullptr)
    {
        delete m_ptr;
        m_ptr = ptr;
    }

    T& operator*() const { return *m_ptr; }

    T* operator->() const { return m_ptr; }

private:
    T* m_ptr;
};

struct ControlBlock 
{
    size_t strong_count;
    size_t weak_count;
    //考虑线程安全 增加：fetch_add(num)  减少：fetch_sub(num) 读取数据 load() 赋值 store(num)
    //std::atomic<size_t> strong_count;
    //std::atomic<size_t> weak_count;
};

template<typename T>
class weak_ptr;

template <typename T>
class shared_ptr {
public:
    shared_ptr() :m_ptr(nullptr), m_ctrl(nullptr) {}

    explicit shared_ptr(T* ptr = nullptr) : m_ptr(ptr), m_ctrl(ptr ? new ControlBlock{ 1, 0 } : nullptr) {}

    explicit shared_ptr(T* ptr, ControlBlock* controlBlock) :m_ptr(ptr), m_ctrl(controlBlock) {}

    shared_ptr(const weak_ptr<T>& weakptr) :m_ptr(weakptr.m_ptr), m_ctrl(weakptr.m_ctrl)
    {
        if (m_ctrl) m_ctrl->strong_count++;
    }

    ~shared_ptr() { decrease_and_destroy(); }

    shared_ptr(const shared_ptr& other) : m_ptr(other.m_ptr), m_ctrl(other.m_ctrl) 
    {
        if (m_ptr) ++m_ctrl->strong_count;
    }

    shared_ptr(shared_ptr&& other) noexcept :m_ptr(other.m_ptr), m_ctrl(other.m_ctrl)
    {
        other.m_ptr = nullptr;
        other.m_ctrl = nullptr;
    }

    shared_ptr& operator=(const shared_ptr& other) 
    {
        if (&other != this) 
        {
            if (other.m_ptr) ++other.m_ctrl->strong_count; 
            decrease_and_destroy(); 
            m_ptr = other.m_ptr;
            m_ctrl = other.m_ctrl;
        }
        return *this;
    }

    shared_ptr& operator=(shared_ptr&& other) noexcept
    {
        if (&other != this)
        {
            decrease_and_destroy();
            m_ptr = other.m_ptr;
            m_ctrl = other.m_ctrl;
            other.m_ctrl = nullptr;
            other.m_ptr = nullptr;
        }
        return *this;
    }

    static shared_ptr make_shared(T* ptr = nullptr)
    {
        //将指针和控制块分配到一块内存中
        struct ControlBlockWithObject : ControlBlock 
        {
            T object;
        };

        auto* ctrl = new ControlBlockWithObject;
        ctrl->strong_count = 1;
        ctrl->weak_count = 0;

        return shared_ptr(&ctrl->object, ctrl);
    }

    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }

private:
    T* m_ptr;
    ControlBlock* m_ctrl;

    void decrease_and_destroy() 
    {
        if (m_ptr && --m_ctrl->strong_count == 0) 
        {
            delete m_ptr;
            if (m_ctrl->weak_count == 0) delete m_ctrl;
        }
    }
};

template <typename T>
class weak_ptr {
public:
    weak_ptr() : m_ptr(nullptr), m_ctrl(nullptr) {}

    weak_ptr(const shared_ptr<T>& spt) : m_ptr(spt.m_ptr), m_ctrl(spt.m_ctrl) 
    {
        if (m_ctrl) ++m_ctrl->weak_count;
    }

    ~weak_ptr() { decrease(); }

    weak_ptr(const weak_ptr& other) : m_ptr(other.m_ptr), m_ctrl(other.m_ctrl) 
    {
        if (m_ctrl) ++m_ctrl->weak_count;
    }

    weak_ptr& operator=(const weak_ptr& other) 
    {
        if (&other != this) 
        {
            if (m_ctrl) ++m_ctrl->weak_count;
            decrease();
            m_ptr = other.m_ptr;
            m_ctrl = other.m_ctrl;
        }
        return *this;
    }

    shared_ptr<T> lock() const 
    {
        if (m_ctrl && m_ctrl->strong_count > 0) return shared_ptr<T>(*this); 
        else return shared_ptr<T>();
    }

private:
    T* m_ptr;
    ControlBlock* m_ctrl;

    void decrease() 
    {
        if (m_ctrl && --m_ctrl->weak_count == 0 && m_ctrl->strong_count == 0) delete m_ctrl;
    }
};