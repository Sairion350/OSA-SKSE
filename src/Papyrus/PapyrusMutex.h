#pragma once

namespace PapyrusMutex
{
    using VM = RE::BSScript::IVirtualMachine;

    std::map<std::string, std::unique_ptr<std::mutex>> mutexDB;

    std::mutex mainmtx;
	

    void MutexLock(RE::StaticFunctionTag*, std::string key){
    	mainmtx.lock();
    	if (mutexDB.count(key) < 1){
    		mutexDB[key] = move(std::make_unique<std::mutex>());
    	}
    	mainmtx.unlock();


    	mutexDB[key]->lock();

    	return;
    }

    void MutexUnlock(RE::StaticFunctionTag*, std::string key){
    	mainmtx.lock();
    	if (mutexDB.count(key) < 1){
    		mainmtx.unlock();
    		return;
    	}
    	mainmtx.unlock();


    	mutexDB[key]->unlock();

    	return;
    }

	bool Bind(VM* a_vm)
	{
		const auto obj = "OSANative"sv;


		BIND(MutexLock);
		BIND(MutexUnlock);

		return true;
	}
}
