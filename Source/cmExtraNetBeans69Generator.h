/*============================================================================
  CMake - Cross Platform Makefile Generator
  Copyright 2004-2009 Kitware, Inc.
  Copyright 2004 Alexander Neundorf (neundorf@kde.org)
  Copyright 2007 Miguel A. Figueroa-Villanueva

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#ifndef cmExtraNetBeans69Generator_h
#define cmExtraNetBeans69Generator_h

#include "cmExternalMakefileProjectGenerator.h"
#include "cmXmlWriter.h"
#include "cmTarget.h"
#include "cmSourceGroup.h"

class cmMakefile;
class cmGeneratedFileStream;

typedef pair<string, string> ATTRIBUTE;

using namespace std;

namespace netbeansgenerator {

  /** \class cmExtraNetBeans69Generator
   * \brief Write NetBeans 6.9 project files for Makefile based projects
   */
  class cmExtraNetBeans69Generator : public cmExternalMakefileProjectGenerator {
  public:

    cmExtraNetBeans69Generator();
    virtual ~cmExtraNetBeans69Generator();

    static cmExternalMakefileProjectGenerator* New();
    static const char* GetActualName();
    virtual const char* GetName() const;
    virtual void GetDocumentation(cmDocumentationEntry& entry, const char* fullName) const;
    virtual void SetGlobalGenerator(cmGlobalGenerator* generator);
    virtual void Generate();

  private:

    void CreateConfigurationFile(cmMakefile& makefile, const cmTarget& target) const;
    void CreateProjectFile(cmMakefile& makefile, const cmTarget& target) const;
    void AddLogicalFolders(cmXmlWriter& xmlWriter, cmMakefile& makefile) const;
    void AddLogicalFolder(cmXmlWriter& xmlWriter, const cmSourceGroup& sourceGroup) const;
    void AddIncludePaths(cmXmlWriter& xmlWriter, cmMakefile& makefile) const;
    void AddCompileFlags(cmXmlWriter& xmlWriter, cmMakefile& makefile) const;
    void CreateProjectFolders(cmMakefile& makefile, const cmTarget& target) const;
    string GetNetBeansDirectory(cmMakefile& makefile) const;
    string GetOutputDirectory(cmMakefile& makefile, const cmTarget& target) const;

    static const string ACTUAL_NAME;
    static const string NETBEANS_DIR;
    static const string FILE_SEPARATOR;

    static const string XML_TAG_PROJECT;
    static const string XML_TAG_TYPE;
    static const string XML_TAG_CONFIGURATION;
    static const string XML_TAG_DATA;
    static const string XML_TAG_NAME;
    static const string XML_TAG_MAKE_PROJECT_TYPE;
    static const string XML_TAG_CEXTENSIONS;
    static const string XML_TAG_CPPEXTENSIONS;
    static const string XML_TAG_HEADEREXTENSIONS;
    static const string XML_TAG_SOURCEENCODING;
    static const string XML_TAG_MAKEDEPPROJECTS;


    static const string XML_TAG_CONFIGURATIONDESCRIPTOR;
    static const string XML_TAG_LOGICALFOLDER;
    static const string XML_TAG_ITEMPATH;
    static const string XML_TAG_SOURCEROOTLIST;
    static const string XML_TAG_ELEM;
    static const string XML_TAG_PROJECTMAKEFILE;
    static const string XML_TAG_CONFS;
    static const string XML_TAG_CONF;
    static const string XML_TAG_TOOLSSET;
    static const string XML_TAG_DEVELOPMENTSERVER;
    static const string XML_TAG_COMPILERSET;
    static const string XML_TAG_PLATFORM;
    static const string XML_TAG_COMPILETYPE;
    static const string XML_TAG_CCTOOL;
    static const string XML_TAG_INCDIR;
    static const string XML_TAG_PELEM;
    static const string XML_TAG_COMMANDLINE;
    static const string XML_TAG_WARNINGLEVEL;
    static const string XML_TAG_LINKERTOOL;
    static const string XML_TAG_OUTPUT;
    static const string XML_TAG_LINKERADDLIB;
    static const string XML_TAG_LINKERDYNSERCH;
    static const string XML_TAG_LINKERLIBITEMS;
    static const string XML_TAG_LINKERLIBLIBITEM;
  };
}
#endif
