#ifndef _CMXMLWRITER_H
#define	_CMXMLWRITER_H

#include <string>
#include <map>
#include <fstream>

using namespace std;

class cmXmlWriter {

public:

  cmXmlWriter(ofstream& outputStream);
  ~cmXmlWriter();
  
  /* @brief Writes an xml tag (opening and closing tags) with a value
   *        and some attributes.
   *
   * @param name The tag name.
   * @param value The value, i.e. the text between opening and closing tag.
   * @param attributes Map of attributes.
   */
  cmXmlWriter& AddTag(const string& name, const string& value, const map<string, string>& attributes);

  /* @brief Writes an xml tag (opening and closing tags) with a value.
   */
  cmXmlWriter& AddTag(const string& name, const string& value);

  /* @brief Writes an xml opening tag with some attributes.
   */
  cmXmlWriter& OpenTag(const string& name, const map<string, string>& attributes);

  /* @brief Writes an xml opening tag.
   */
  cmXmlWriter& OpenTag(const string& name);

  /* @brief Writes an xml closing tag.
   */
  cmXmlWriter& CloseTag(const string& name);

  /* @brief Writes some text to the xml file, mainly for values after an
   *        opening tag.
   */
  cmXmlWriter& Write(const string& text);

private:

  static const string INDENT;
  static const string HEADER;

  ofstream& outputStream;
  int indentation;

  cmXmlWriter& IndentationDecrease();
  cmXmlWriter& IndentationIncrease();
  
  cmXmlWriter& Indentation();
  cmXmlWriter& Newline();
  cmXmlWriter& AddHeader();

  /* @brief Internal open tag method.
   *
   * The internal method differs from the public one because there is
   * no newline. When the user calls the public function, there will
   * always be a newline.
   */
  cmXmlWriter& OpenTagInternal(const string& name, const map<string, string>& attributes);
  
  /* @brief Internal open tag method.
   *
   * The internal method differ from the public one because there is
   * no newline. When the user calls the public function, there will
   * always be a newline.
   */
  cmXmlWriter& OpenTagInternal(const string& name);

  /* @brief Internal closing tag method.
   *
   * The internal method differ from the public one because there is
   * no indentation. When the user calls the public function, there will
   * always be indentation.
   */
  cmXmlWriter& CloseTagInternal(const string& name);
};

#endif	/* _CMXMLWRITER_H */

