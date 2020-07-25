#pragma once

#include <list>
#include "main.h"


class CResource
{

protected:

	char							m_FileName[ MAX_PATH ];

	static std::list<CResource*>	m_Pool;

public:

	CResource(){}
	virtual ~CResource(){}


	virtual void Load( const char* FileName ) = 0;
	virtual void Unload() = 0;





	template <typename T>
	static T* Load( const char* FileName )
	{
		for( CResource* resource : m_Pool )
		{
			if( strcmp( resource->m_FileName, FileName ) == 0 )
			{
				return (T*)resource;
			}
		}

		T* resource = new T();
		resource->Load( FileName );
		strcpy( resource->m_FileName, FileName );
		m_Pool.push_back( resource );

		return resource;
	}


	template <typename T>
	static T* Create(const char* Name)
	{

		T* resource = new T();
		strcpy(resource->m_FileName, Name);
		m_Pool.push_back(resource);

		return resource;
	}



	static void UnloadAll()
	{

		for( CResource* resource : m_Pool )
		{
			resource->Unload();
			delete resource;
		}

		m_Pool.clear();
	}

};