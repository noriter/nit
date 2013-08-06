/// nit - Noriter Framework
/// A Cross-platform Open Source Integration for Game-oriented Apps
///
/// http://www.github.com/ellongrey/nit
///
/// Copyright (c) 2013 by Jun-hyeok Jang
/// 
/// (see each file to see the different copyright owners)
/// 
/// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
/// 
/// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
/// 
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
///
/// Author: ellongrey

#include "nitdevkit_pch.h"

#include "nitdevkit/NitDevParser.h"

#include "nit/script/NitBind.h"
#include "nit/script/NitBindMacro.h"

NS_NIT_BEGIN;

////////////////////////////////////////////////////////////////////////////////

NB_TYPE_AUTODELETE(NITDEVKIT_API, nitdev::NitLexer, NULL, delete);

class NB_NitLexer : TNitClass<nitdev::NitLexer>
{
public:
	static void Register(HSQUIRRELVM v)
	{
		PropEntry props[] =
		{
			NULL
		};

		FuncEntry funcs[] =
		{
			CONS_ENTRY_H(				"()"),
			FUNC_ENTRY_H(start,			"(reader: StreamReader)"
			"\n"						"(str: string)"),
			FUNC_ENTRY_H(lex,			"(): TOKEN"),
			NULL
		};

		bind(v, props, funcs);
	}

	NB_CONS()							{ setSelf(v, new type()); return SQ_OK; }

	NB_FUNC(start)
	{
		if (isString(v, 2))
		{
			size_t len = sq_getsize(v, 2);
			self(v)->start(getString(v, 2), len);
		}
		else
		{
			self(v)->start(get<StreamReader>(v, 2));
		}
		return 0;
	}

	NB_FUNC(lex)						{ return push(v, (int) self(v)->lex()); }
};

////////////////////////////////////////////////////////////////////////////////

NITDEVKIT_API SQRESULT NitLibDevKit(HSQUIRRELVM v)
{
	nitdev::NB_NitLexer::Register(v);
	return SQ_OK;
}

////////////////////////////////////////////////////////////////////////////////

NS_NIT_END;
