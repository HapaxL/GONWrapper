#pragma once

#include "../GON/gon.h"

using namespace System;

namespace GonWrapper
{
	public ref class GonObject
	{
		GON::GonObject* m_Instance;

	public:
		GonObject();
		GonObject(GON::GonObject obj);
		~GonObject() { this->!GonObject(); }
		!GonObject() { delete m_Instance; }

		enum class FieldType {
			NULLGON,
			STRING,
			NUMBER,
			OBJECT,
			ARRAY,
			BOOL
		};

		String^ Name;

		static GonObject^ Load(String^ filename);

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

		GonObject^ operator[](String^ child);
		GonObject^ Get(String^ child);

		GonObject^ ChildOrSelf(String^ child);

		GonObject^ operator[](int childindex);
		GonObject^ Get(int childindex);
		int Size();

		void Save(String^ outfilename);

		void InsertChild(GonObject^ other);
		void InsertChild(String^ name, GonObject^ other);

		void Append(GonObject^ other);

		// my own methods
		String^ GetFieldTypeAsString();

		static GonObject^ FromInt(int value);
		static GonObject^ FromNumber(double value);
		static GonObject^ FromBool(bool value);
		static GonObject^ FromString(String^ value);

		static GonObject^ MakeEmptyObject();
		static GonObject^ MakeEmptyArray();
	};
}