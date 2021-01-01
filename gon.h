#pragma once

#include "../GON/gon.h"

using namespace System;

namespace GonWrapper
{
	public ref class GonWObject
	{
		GonObject* m_Instance;

	public:
		GonWObject();
		GonWObject(GonObject obj);
		~GonWObject() { this->!GonWObject(); }
		!GonWObject() { delete m_Instance; }

		enum class FieldType {
			NULLGON,
			STRING,
			NUMBER,
			OBJECT,
			ARRAY,
			BOOL
		};

		String^ Name;

		static GonWObject^ Load(String^ filename);

		String^ GetString();
		const char* GetCharArray();
		int GetInt();
		double GetNumber();
		bool GetBool();

		String^ GetString(String^ _default);
		const char* GetCharArray(const char* _default);
		int GetInt(int _default);
		double GetNumber(double _default);
		bool GetBool(bool _default);

		bool Contains(String^ child);
		bool Contains(int child);
		bool Exists();

		GonWObject^ operator[](String^ child);
		GonWObject^ Get(String^ child);

		GonWObject^ ChildOrSelf(String^ child);

		GonWObject^ operator[](int childindex);
		GonWObject^ Get(int childindex);
		int Size();

		void Save(String^ outfilename);

		void InsertChild(GonWObject^ other);
		void InsertChild(String^ name, GonWObject^ other);

		void Append(GonWObject^ other);

		// my own methods
		String^ GetFieldTypeAsString();

		static GonWObject^ FromInt(int value);
		static GonWObject^ FromNumber(double value);
		static GonWObject^ FromBool(bool value);
		static GonWObject^ FromString(String^ value);

		static GonWObject^ MakeEmptyObject();
		static GonWObject^ MakeEmptyArray();
	};
}