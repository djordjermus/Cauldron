#include <vector>
#pragma once
namespace cauldron::common {

	  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	 // C A L L B A C K - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	template<class R, class... ArgTs>
	class callback {
	public:

		R invoke(ArgTs... args) {
			return (*this.*_invoke_fn)(args...);
		}

		callback() :
			_invoke_fn(&callback::noInvoke),
			_function(nullptr),
			_pobj(nullptr) {}
		callback(R (*function)(ArgTs...)) :
			_invoke_fn(&callback::fnInvoke),
			_function(reinterpret_cast<void*>(function)),
			_pobj(nullptr) {}

		template<R(*method)(ArgTs...)>
		static callback make() {
			callback ret;
			ret._invoke_fn	= &callback::fnInvoke;
			ret._function	= reinterpret_cast<void*>(method);
			ret._pobj		= nullptr;

			return ret;
		}
		template<class T, R (T::*method)(ArgTs...)>
		static callback make(T* object) {
			callback ret;
			ret._invoke_fn	= &callback::mbInvoke;
			ret._function	= reinterpret_cast<void*>(&fnCallMember<T, method>);
			ret._pobj		= object;

			return ret;
		}
		bool operator==(const callback& rhs) {
			return
				_invoke_fn == rhs._invoke_fn &&
				_function == rhs._function &&
				_pobj == rhs._pobj;
		}
		bool operator!=(const callback& rhs) {
			return
				_invoke_fn != rhs._invoke_fn ||
				_function != rhs._function ||
				_pobj != rhs._pobj;
		}
	private:
		R noInvoke(ArgTs...) {
			throw;
		}
		R fnInvoke(ArgTs... args) {
			return (reinterpret_cast<R(*)(ArgTs...)>(_function))(args...);
		}
		R mbInvoke(ArgTs... args) {
			return (reinterpret_cast<R(*)(void*, ArgTs...)>(_function))(_pobj, args...);
		}
		template<class T, R(T::*method)(ArgTs...)>
		static R fnCallMember(void* pobj, ArgTs... args) {
			return (*(T*)pobj.*method)(args...);
		}

		R(callback::* _invoke_fn)(ArgTs...)
			= nullptr;
		void* _function
			= nullptr;
		void* _pobj
			= nullptr;
	};

	  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	 // O B S E R V A B L E - - - - - - - - - - - - - - - - - - - - - - - - - -
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


	template<class R, class... ArgTs>
	class observable {
	public:
		using callback_t = callback<R, ArgTs...>;
		observable() :
			_callbacks() {}
		virtual ~observable() {}

		void subscribe(const callback_t& cb) {
			_callbacks.emplace_back(cb);
		}
		void subscribe(const observable& o) {
			_callbacks.insert(_callbacks.end(), o._callbacks.begin(), o._callbacks.end());
		}
		void unsubscribe(const callback_t& cb) {
			for (auto it = _callbacks.begin(), jt = _callbacks.end(); it != jt; it++) {
				if (*it == cb) {
					_callbacks.erase(it);
					return;
				}
			}
		}
		void unsubscribe(const observable& o) {
			if (this == &o) {
				_callbacks.clear();
				return;
			}

			for (auto it = o._callbacks.begin(), jt = o._callbacks.end(); it != jt; it++)
				unsubscribe(*it);
		}
		void notify(ArgTs... args) {
			for (unsigned long long i = 0; i < _callbacks.size(); i++)
				_callbacks[i].invoke(args...);
		}
		void clear() { _callbacks.clear(); }

	private:
		std::vector<callback_t> _callbacks
			= std::vector<callback_t>();
	};
}