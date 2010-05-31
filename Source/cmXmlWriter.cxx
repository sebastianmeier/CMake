#include <sstream>

#include "cmXmlWriter.h"
#include "cmXMLSafe.h"

const string cmXmlWriter::INDENT = "    ";
const string cmXmlWriter::HEADER = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";

cmXmlWriter::cmXmlWriter(ofstream& outputStream) : outputStream(outputStream), indentation(0) {
  AddHeader().Newline();
}

cmXmlWriter::~cmXmlWriter() {
  outputStream.close();
}

cmXmlWriter& cmXmlWriter::AddTag(const string& name, const string& value, const map<string, string>& attributes) {
  OpenTagInternal(name, attributes).Write(value).CloseTagInternal(name);
  return *this;
}

cmXmlWriter& cmXmlWriter::AddTag(const string& name, const string& value) {
  OpenTagInternal(name).Write(value).CloseTagInternal(name);
  return *this;
}

cmXmlWriter& cmXmlWriter::OpenTag(const string& name, const map<string,string>& attributes) {
  return OpenTagInternal(name, attributes).Newline().IndentationIncrease();
}

cmXmlWriter& cmXmlWriter::OpenTagInternal(const string& name, const map<string, string>& attributes) {
  
  Indentation();

  outputStream << "<" << name;

  map<string, string>::const_iterator it = attributes.begin();
  while (it != attributes.end()) {
    outputStream << " ";
    outputStream << it->first << "=\"" << cmXMLSafe(it->second) << "\"";
    it++;
  }

  outputStream << ">";

  return *this;
}

cmXmlWriter& cmXmlWriter::OpenTag(const string& name) {
  return OpenTagInternal(name).Newline().IndentationIncrease();
}

cmXmlWriter& cmXmlWriter::OpenTagInternal(const string& name) {
  OpenTagInternal(name, map<string, string>());
  return *this;
}

cmXmlWriter& cmXmlWriter::CloseTag(const string& name) {
  IndentationDecrease().Indentation().CloseTagInternal(name);
}

cmXmlWriter& cmXmlWriter::CloseTagInternal(const string& name) {
  outputStream << "</" << name << ">";
  Newline();
  return *this;
}

cmXmlWriter& cmXmlWriter::Write(const string& text) {
  outputStream << text;
  return *this;
}

cmXmlWriter& cmXmlWriter::IndentationIncrease() {
  indentation++;
  return *this;
}

cmXmlWriter& cmXmlWriter::IndentationDecrease() {
  indentation--;
  return *this;
}

cmXmlWriter& cmXmlWriter::Indentation() {
  for (int i = 0; i < indentation; i++) {
    outputStream << INDENT;
  }
  return *this;
}

cmXmlWriter& cmXmlWriter::Newline() {
  outputStream << endl;
  return *this;
}

cmXmlWriter& cmXmlWriter::AddHeader() {
  outputStream << HEADER;
  return *this;
}


