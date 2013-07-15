typedef struct _GUID GUID;

typedef GUID IID;
typedef unsigned short *String;
#define MaxWordLength 32
struct DictWord
{
	char wordForLang1[MaxWordLength];
	char wordForLang2[MaxWordLength];
};

class IUnKnown
{
public:
	virtual HRESULT _stdcall QueryInterface(const IID& iid, void** ppv) = 0;
	virtual ULONG _stdcall AddRef() = 0;
	virtual ULONG _stdcall Release() = 0;
};
class IDictionary : public IUnKnown
{
public:
	virtual BOOL _stdcall Initialize() = 0;
	virtual BOOL _stdcall LoadLibrary() = 0;
	virtual BOOL _stdcall InsertWord(String, String) = 0;
	virtual void _stdcall DeleteWord(String) = 0;
	virtual BOOL _stdcall LookupWord(String, String*) = 0;
	virtual BOOL _stdcall RestoreLibrary(String) = 0;
	virtual void _stdcall FreeLibrary() = 0;
};
class CDictionary : public IDictionary
{
public:
	CDictionary();
	~CDictionary();
public:
	virtual HRESULT _stdcall QueryInterface(const IID& iid, void** ppv);
	virtual ULONG _stdcall AddRef();
	virtual ULONG _stdcall Release();
	virtual BOOL _stdcall Initialize();
	virtual BOOL _stdcall LoadLibrary();
	virtual BOOL _stdcall InsertWord(String, String);
	virtual void _stdcall DeleteWord(String);
	virtual BOOL _stdcall LookupWord(String, String*);
	virtual BOOL _stdcall RestoreLibrary(String);
	virtual void _stdcall FreeLibrary();
private:
	struct DictWord* m_pData;
	char* m_szDictFileName[128];
	int m_nRef;
};