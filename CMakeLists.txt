cmake_minimum_required(VERSION 3.7)
project(cosmos)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(./object_pool)
include_directories(./pattern)
include_directories(./self-register-factory)
include_directories(./tuple)
include_directories(./worksteal)

add_executable(cosmos
        object_pool/SimpleObjectPool.hpp
        pattern/Command.hpp
        pattern/ObjectPool.hpp
        pattern/Observer.hpp
        pattern/Singleton.hpp
        pattern/Visitor.hpp
        self-register-factory/Message.hpp
        self-register-factory/Message1.hpp
        self-register-factory/MessageFactory.hpp
        self-register-factory/MessageFatory1.hpp
        tuple/TpApply.hpp
        tuple/TpForeach.hpp
        tuple/TpIndexs.hpp
        tuple/TpPrint.hpp
        tuple/TpZip.hpp
        worksteal/main.cpp
        worksteal/sync_deque.hpp
        worksteal/thread_pool.hpp
        worksteal/worker.hpp
        Any.hpp
        Aspect.hpp
        Bind.hpp
        cache.hpp
        DllParser.hpp
        Format.hpp
        fun_test.hpp
        function_message_bus.hpp
        function_traits.hpp
        Ioc.hpp
        Lazy.hpp
        lexical_cast.hpp
        LinqCpp.hpp
        MessageBus.hpp
        modern_functor.hpp
        modern_messagebus.hpp
        Nan-boxing.hpp
        NonCopyable.hpp
        Optional.hpp
        pod_reflection.hpp
        Range.hpp
        reflection.hpp
        router.hpp
        ScopeGuard.hpp
        SharedptrUtil.hpp
        SyncQueue.hpp
        ThreadPool.hpp
        Timer.hpp
        type_name.hpp
        variadic2tuple.hpp
        Variant.hpp)

add_executable(module_test test.cpp Any.hpp Aspect.hpp)
