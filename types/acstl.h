namespace ACSTD {
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
}