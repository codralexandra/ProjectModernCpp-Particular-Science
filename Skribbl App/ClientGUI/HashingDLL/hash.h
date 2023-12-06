
#include <string>
//#ifndef HashingDLL_EXPORTS
//#define HASH_API __declspec(dllexport)
//#else 
//#define HASH_API __declspec(dllimport)
//#endif 
class __declspec(dllexport) HashMethod
{
public:
	HashMethod() = default;
	void Set(std::string pas);
	std::string Get();
	void SetHashedPass();
private:
	std::string m_password;

private:
	int Hash();

};
