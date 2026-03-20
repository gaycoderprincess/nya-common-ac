namespace ACSTD {
	template<typename T, typename T2>
	class map {
	public:
		uint8_t _0[0x10];
	};

	template<typename T>
	class function {
	public:
		uint8_t _0[0x20];
	};

	class string {
	public:
		union _Bxty {
			char _Buf[16];
			char *_Ptr;
			char _Alias[16];
		};

		_Bxty _Bx;
		unsigned __int64 _Mysize;
		unsigned __int64 _Myres;

		auto assign(const char* _Ptr, uint64_t _Count) { auto f = (string*(__fastcall*)(string*, const char*, uint64_t))(NyaHookLib::mEXEBase + 0x1CF80); return f(this, _Ptr, _Count); }
	};
	static_assert(sizeof(string) == 0x20);

	class wstring {
	public:
		union _Bxty {
			wchar_t _Buf[8];
			wchar_t *_Ptr;
			char _Alias[8];
		};

		_Bxty _Bx;
		unsigned __int64 _Mysize;
		unsigned __int64 _Myres;

		auto assign(const wchar_t* _Ptr, uint64_t _Count) { auto f = (wstring*(__fastcall*)(wstring*, const wchar_t*, uint64_t))(NyaHookLib::mEXEBase + 0x1D250); return f(this, _Ptr, _Count); }
	};
	static_assert(sizeof(wstring) == 0x20);

	template<typename T>
	class unique_ptr {
	public:
		T *_Myptr;
	};
	static_assert(sizeof(unique_ptr<void>) == 0x8);

	template<typename T>
	class vector {
	public:
		T *_Myfirst;
		T *_Mylast;
		T *_Myend;
	};
	static_assert(sizeof(vector<void>) == 0x18);

	template<typename T1, typename T2>
	class pair {
	public:
		T1 first;
		T2 *second;
	};
}