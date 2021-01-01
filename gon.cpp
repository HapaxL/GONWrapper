// convert_standard_string_to_system_string.cpp
// compile with: /clr
#include "gon.h"
#include <string>
#include <iostream>
using namespace System;
using namespace std;
using namespace System::Runtime::InteropServices;

static const char* string_to_char_array(String^ string)
{
	const char* str = (const char*)(Marshal::StringToHGlobalAnsi(string)).ToPointer();
	return str;
}

String^ string_to_managed_string(std::string str)
{
	return gcnew String(str.c_str());
}

namespace GonWrapper
{
	GonObject::GonObject()
	{
		m_Instance = new GON::GonObject();
	}

	GonObject::GonObject(GON::GonObject obj)
	{
		m_Instance = new GON::GonObject();
		m_Instance->children_map = obj.children_map;
		m_Instance->children_array = obj.children_array;
		m_Instance->int_data = obj.int_data;
		m_Instance->float_data = obj.float_data;
		m_Instance->bool_data = obj.bool_data;
		m_Instance->string_data = obj.string_data;
		m_Instance->name = obj.name;
		this->Name = string_to_managed_string(obj.name);
		m_Instance->type = obj.type;
	}

	GonObject^ GonObject::Load(String^ filename)
	{
		std::string str = string_to_char_array(filename);
		GON::GonObject obj = GON::GonObject::Load(str);
		GonObject^ res = gcnew GonObject(obj);
		return res;
	}

	String^ GonObject::GetString()
	{
		std::string res = m_Instance->String();
		return string_to_managed_string(res);
	}

	const char* GonObject::GetCharArray()
	{
		return m_Instance->CString();
	}

	int GonObject::GetInt()
	{
		return m_Instance->Int();
	}

	double GonObject::GetNumber()
	{
		return m_Instance->Number();
	}

	bool GonObject::GetBool()
	{
		return m_Instance->Bool();
	}

	String^ GonObject::GetString(String^ _default)
	{
		std::string str = string_to_char_array(_default);
		std::string res = m_Instance->String(str);
		return string_to_managed_string(res);
	}

	const char* GonObject::GetCharArray(const char* _default)
	{
		return m_Instance->CString(_default);
	}

	int GonObject::GetInt(int _default)
	{
		return m_Instance->Int(_default);
	}

	double GonObject::GetNumber(double _default)
	{
		return m_Instance->Number(_default);
	}

	bool GonObject::GetBool(bool _default)
	{
		return m_Instance->Bool(_default);
	}

	bool GonObject::Contains(String^ child)
	{
		std::string str = string_to_char_array(child);
		return m_Instance->Contains(str);
	}

	bool GonObject::Contains(int child)
	{
		return m_Instance->Contains(child);
	}

	bool GonObject::Exists()
	{
		return m_Instance->Exists();
	}

	GonObject^ GonObject::operator[](String^ child)
	{
		std::string str = string_to_char_array(child);
		return gcnew GonObject((*m_Instance)[str]);
	}

	GonObject^ GonObject::Get(String^ child)
	{
		std::string str = string_to_char_array(child);
		return gcnew GonObject((*m_Instance)[str]);
	}

	GonObject^ GonObject::ChildOrSelf(String^ child)
	{
		std::string str = string_to_char_array(child);
		return gcnew GonObject(m_Instance->ChildOrSelf(str));
	}

	GonObject^ GonObject::operator[](int childindex)
	{
		return gcnew GonObject((*m_Instance)[childindex]);
	}

	GonObject^ GonObject::Get(int childindex)
	{
		return gcnew GonObject((*m_Instance)[childindex]);
	}

	int GonObject::Size()
	{
		return m_Instance->Size();
	}

	void GonObject::Save(String^ outfilename)
	{
		std::string str = string_to_char_array(outfilename);
		m_Instance->Save(str);
	}

	void GonObject::InsertChild(GonObject^ other)
	{
		m_Instance->InsertChild(*other->m_Instance);
	}

	void GonObject::InsertChild(String^ name, GonObject^ other)
	{
		std::string str = string_to_char_array(name);
		m_Instance->InsertChild(str, *other->m_Instance);
	}

	void GonObject::Append(GonObject^ other)
	{
		m_Instance->Append(*other->m_Instance);
	}

	String^ GonObject::GetFieldTypeAsString()
	{
		switch (m_Instance->type)
		{
		case GON::GonObject::FieldType::ARRAY:
			return "ARRAY";
		case GON::GonObject::FieldType::BOOL:
			return "BOOL";
		case GON::GonObject::FieldType::NULLGON:
			return "NULLGON";
		case GON::GonObject::FieldType::NUMBER:
			return "NUMBER";
		case GON::GonObject::FieldType::OBJECT:
			return "OBJECT";
		case GON::GonObject::FieldType::STRING:
			return "STRING";
		default:
			return "what";
		}
	}

	GonObject^ GonObject::FromInt(int value)
	{
		GON::GonObject* obj = new GON::GonObject();
		obj->string_data = string_to_char_array(value.ToString());
		obj->int_data = value;
		obj->type = GON::GonObject::FieldType::NUMBER;
		return gcnew GonObject(*obj);
	}

	GonObject^ GonObject::FromNumber(double value)
	{
		GON::GonObject* obj = new GON::GonObject();
		obj->string_data = string_to_char_array(value.ToString());
		obj->float_data = value;
		obj->type = GON::GonObject::FieldType::NUMBER;
		return gcnew GonObject(*obj);
	}

	GonObject^ GonObject::FromBool(bool value)
	{
		GON::GonObject* obj = new GON::GonObject();
		obj->string_data = string_to_char_array(value.ToString());
		obj->bool_data = value;
		obj->type = GON::GonObject::FieldType::BOOL;
		return gcnew GonObject(*obj);
	}

	GonObject^ GonObject::FromString(String^ value)
	{
		GON::GonObject* obj = new GON::GonObject();
		obj->string_data = string_to_char_array(value);
		obj->type = GON::GonObject::FieldType::STRING;
		return gcnew GonObject(*obj);
	}

	GonObject^ GonObject::MakeEmptyObject()
	{
		GON::GonObject* obj = new GON::GonObject();
		obj->type = GON::GonObject::FieldType::OBJECT;
		return gcnew GonObject(*obj);
	}

	GonObject^ GonObject::MakeEmptyArray()
	{
		GON::GonObject* obj = new GON::GonObject();
		obj->type = GON::GonObject::FieldType::ARRAY;
		return gcnew GonObject(*obj);
	}
}