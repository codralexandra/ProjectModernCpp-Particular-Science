export module hash;
import <string>;

export class __declspec(dllexport) HashMethod
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
