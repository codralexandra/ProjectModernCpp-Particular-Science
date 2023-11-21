export module hash;
import <string>;

export class __declspec(dllexport) HashMethod
{
public:
	void Set(std::string pas);
	std::string Get();
	void SetHashedPass();
private:
	std::string m_password;

private:
	int Hash();
public:

	HashMethod() = default;
};
