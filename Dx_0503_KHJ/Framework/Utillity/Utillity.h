#pragma once

static std::string WstringToString(wstring wstr)
{
	std::string t;
	t.reserve(wstr.length() + 1);
	for (auto c : wstr)
	{
		t.push_back(c);
	}

	return t;
}

