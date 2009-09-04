//
// DirectoryIterator.cpp
//
// $Id: //poco/svn/Foundation/src/DirectoryIterator.cpp#2 $
//
// Library: Foundation
// Package: Filesystem
// Module:  DirectoryIterator
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "Poco/DirectoryIterator.h"


#if defined(POCO_OS_FAMILY_WINDOWS) && defined(POCO_WIN32_UTF8)
#include "DirectoryIterator_WIN32U.cpp"
#elif defined(POCO_OS_FAMILY_WINDOWS)
#include "DirectoryIterator_WIN32.cpp"
#elif defined(POCO_OS_FAMILY_UNIX)
#include "DirectoryIterator_UNIX.cpp"
#else
#include "DirectoryIterator_VMS.cpp"
#endif


namespace Poco {


DirectoryIterator::DirectoryIterator(): _pImpl(0)
{
}

	
DirectoryIterator::DirectoryIterator(const std::string& path): _path(path), _pImpl(new DirectoryIteratorImpl(path))
{
	_path.makeDirectory();
	_path.setFileName(_pImpl->get());
	_file = _path;
}


DirectoryIterator::DirectoryIterator(const DirectoryIterator& iterator): _path(iterator._path), _pImpl(iterator._pImpl)
{
	if (_pImpl) 
	{
		_pImpl->duplicate();
		_file = _path;
	}
}

	
DirectoryIterator::DirectoryIterator(const File& file): _path(file.path()), _pImpl(new DirectoryIteratorImpl(file.path()))
{
	_path.makeDirectory();
	_path.setFileName(_pImpl->get());
	_file = _path;
}


DirectoryIterator::DirectoryIterator(const Path& path): _path(path), _pImpl(new DirectoryIteratorImpl(path.toString()))
{
	_path.makeDirectory();
	_path.setFileName(_pImpl->get());
	_file = _path;
}


DirectoryIterator::~DirectoryIterator()
{
	if (_pImpl) _pImpl->release();
}


DirectoryIterator& DirectoryIterator::operator = (const DirectoryIterator& it)
{
	if (_pImpl) _pImpl->release();
	_pImpl = it._pImpl;
	if (_pImpl) 
	{
		_pImpl->duplicate();
		_path = it._path;
		_file = _path;
	}
	return *this;
}


DirectoryIterator& DirectoryIterator::operator = (const File& file)
{
	if (_pImpl) _pImpl->release();
	_pImpl = new DirectoryIteratorImpl(file.path());
	_path.parseDirectory(file.path());
	_path.setFileName(_pImpl->get());
	_file = _path;
	return *this;
}


DirectoryIterator& DirectoryIterator::operator = (const Path& path)
{
	if (_pImpl) _pImpl->release();
	_pImpl = new DirectoryIteratorImpl(path.toString());
	_path = path;
	_path.makeDirectory();
	_path.setFileName(_pImpl->get());
	_file = _path;
	return *this;
}


DirectoryIterator& DirectoryIterator::operator = (const std::string& path)
{
	if (_pImpl) _pImpl->release();
	_pImpl = new DirectoryIteratorImpl(path);
	_path.parseDirectory(path);
	_path.setFileName(_pImpl->get());
	_file = _path;
	return *this;
}


DirectoryIterator& DirectoryIterator::operator ++ ()
{
	if (_pImpl)
	{
		_path.setFileName(_pImpl->next());
		_file = _path;
	}
	return *this;
}


DirectoryIterator DirectoryIterator::operator ++ (int dummy)
{
	if (_pImpl)
	{
		_path.setFileName(_pImpl->next());
		_file = _path;
	}
	return *this;
}


} // namespace Poco
