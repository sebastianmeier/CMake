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
#include "cmExtraNetBeans69Generator.h"
#include "cmGlobalUnixMakefileGenerator3.h"
#include "cmLocalUnixMakefileGenerator3.h"
#include "cmMakefile.h"
#include "cmGeneratedFileStream.h"

#include "cmSystemTools.h"
#include "cmSourceFile.h"
#include "cmXMLSafe.h"
#include <stdlib.h>
#include <assert.h>

namespace netbeansgenerator {

  const string cmExtraNetBeans69Generator::ACTUAL_NAME = "NetBeans 6.9";
  const string cmExtraNetBeans69Generator::NETBEANS_DIR = "nbproject";
  const string cmExtraNetBeans69Generator::FILE_SEPARATOR = "/";

  const string cmExtraNetBeans69Generator::XML_TAG_PROJECT = "project";
  const string cmExtraNetBeans69Generator::XML_TAG_TYPE = "type";
  const string cmExtraNetBeans69Generator::XML_TAG_CONFIGURATION = "configuration";
  const string cmExtraNetBeans69Generator::XML_TAG_DATA = "data";
  const string cmExtraNetBeans69Generator::XML_TAG_NAME = "name";
  const string cmExtraNetBeans69Generator::XML_TAG_MAKE_PROJECT_TYPE = "make-project-type";
  const string cmExtraNetBeans69Generator::XML_TAG_CEXTENSIONS = "c-extensions";
  const string cmExtraNetBeans69Generator::XML_TAG_CPPEXTENSIONS = "cpp-extensions";
  const string cmExtraNetBeans69Generator::XML_TAG_HEADEREXTENSIONS = "header-extensions";
  const string cmExtraNetBeans69Generator::XML_TAG_SOURCEENCODING = "sourceEncoding";
  const string cmExtraNetBeans69Generator::XML_TAG_MAKEDEPPROJECTS = "make-dep-projects";

  const string cmExtraNetBeans69Generator::XML_TAG_CONFIGURATIONDESCRIPTOR = "configurationDescriptor";
  const string cmExtraNetBeans69Generator::XML_TAG_LOGICALFOLDER = "logicalFolder";
  const string cmExtraNetBeans69Generator::XML_TAG_ITEMPATH = "itemPath";
  const string cmExtraNetBeans69Generator::XML_TAG_SOURCEROOTLIST = "sourceRootList";
  const string cmExtraNetBeans69Generator::XML_TAG_ELEM = "Elem";
  const string cmExtraNetBeans69Generator::XML_TAG_PROJECTMAKEFILE = "projectmakefile";
  const string cmExtraNetBeans69Generator::XML_TAG_CONFS = "confs";
  const string cmExtraNetBeans69Generator::XML_TAG_CONF = "conf";
  const string cmExtraNetBeans69Generator::XML_TAG_TOOLSSET = "toolsSet";
  const string cmExtraNetBeans69Generator::XML_TAG_DEVELOPMENTSERVER = "developmentServer";
  const string cmExtraNetBeans69Generator::XML_TAG_COMPILERSET = "compilerSet";
  const string cmExtraNetBeans69Generator::XML_TAG_PLATFORM = "platform";
  const string cmExtraNetBeans69Generator::XML_TAG_COMPILETYPE = "compileType";
  const string cmExtraNetBeans69Generator::XML_TAG_CCTOOL = "ccTool";
  const string cmExtraNetBeans69Generator::XML_TAG_INCDIR = "incDir";
  const string cmExtraNetBeans69Generator::XML_TAG_PELEM = "pElem";
  const string cmExtraNetBeans69Generator::XML_TAG_COMMANDLINE = "commandLine";
  const string cmExtraNetBeans69Generator::XML_TAG_WARNINGLEVEL = "warningLevel";
  const string cmExtraNetBeans69Generator::XML_TAG_LINKERTOOL = "linkerTool";
  const string cmExtraNetBeans69Generator::XML_TAG_OUTPUT = "ouptut";
  const string cmExtraNetBeans69Generator::XML_TAG_LINKERADDLIB = "linkerAddLib";
  const string cmExtraNetBeans69Generator::XML_TAG_LINKERDYNSERCH = "linkerDynSerch";
  const string cmExtraNetBeans69Generator::XML_TAG_LINKERLIBITEMS = "linkerLibItems";
  const string cmExtraNetBeans69Generator::XML_TAG_LINKERLIBLIBITEM = "linkerLibLibItem";

  cmExternalMakefileProjectGenerator* cmExtraNetBeans69Generator::New() {
    return new cmExtraNetBeans69Generator();
  }

  const char* cmExtraNetBeans69Generator::GetName() const {
    return GetActualName();
  }

  cmExtraNetBeans69Generator::cmExtraNetBeans69Generator() : cmExternalMakefileProjectGenerator() {
#if defined(_WIN32)
    SupportedGlobalGenerators.push_back("NMake Makefiles");
    SupportedGlobalGenerators.push_back("MinGW Makefiles");
#endif
    SupportedGlobalGenerators.push_back("Unix Makefiles");
  }

  cmExtraNetBeans69Generator::~cmExtraNetBeans69Generator() {
    // nop
  }

  void cmExtraNetBeans69Generator::GetDocumentation(cmDocumentationEntry& entry, const char*) const {
    entry.Name = GetName();
    entry.Brief = "Generates NetBeans 6.9 project files.";
    entry.Full = "Generates NetBeans 6.9 project files.";
  }

  void cmExtraNetBeans69Generator::SetGlobalGenerator(cmGlobalGenerator* generator) {
    cmExternalMakefileProjectGenerator::SetGlobalGenerator(generator);
    cmGlobalUnixMakefileGenerator3* globalUnixMakeFileGenerator3 = static_cast<cmGlobalUnixMakefileGenerator3*> (generator);
    globalUnixMakeFileGenerator3->SetToolSupportsColor(true);
  }

  void cmExtraNetBeans69Generator::Generate() {

    cmMakefile& makefile =
      *(GlobalGenerator->GetLocalGenerators()[0]->GetMakefile());

    cmTargets& targets = makefile.GetTargets();
    for (cmTargets::const_iterator it = targets.begin(); it != targets.end(); it++) {

      const cmTarget& target = it->second;

      // only executables are supported as of now
      if (target.GetType() != cmTarget::EXECUTABLE) {
        continue;
      }

      CreateProjectFolders(makefile, target);
      CreateProjectFile(makefile, target);
      CreateConfigurationFile(makefile, target);
    }
  }

  void cmExtraNetBeans69Generator::CreateProjectFile(cmMakefile& makefile, const cmTarget& target) const {

    const string filename =
      GetOutputDirectory(makefile, target) + FILE_SEPARATOR + "project.xml";

    cmGeneratedFileStream fout(filename.c_str());
    if (!fout) {
      return;
    }
    cmXmlWriter xmlWriter(fout);

    map<string, string> attributes;

    // project container
    attributes.clear();
    attributes.insert(ATTRIBUTE("xmlns", "http://www.netbeans.org/ns/project/1"));
    xmlWriter.OpenTag(XML_TAG_PROJECT, attributes);

    // project type
    xmlWriter.AddTag(XML_TAG_TYPE, "org.netbeans.modules.cnd.makeproject");

    // configuration container
    xmlWriter.OpenTag(XML_TAG_CONFIGURATION);

    // data container
    attributes.clear();
    attributes.insert(ATTRIBUTE("xmlns", "http://www.netbeans.org/ns/make-project/1"));
    xmlWriter.OpenTag(XML_TAG_DATA, attributes);

    xmlWriter.AddTag(XML_TAG_NAME, "foo");
    xmlWriter.AddTag(XML_TAG_MAKE_PROJECT_TYPE, "foo");
    xmlWriter.AddTag(XML_TAG_CEXTENSIONS, "foo");
    xmlWriter.AddTag(XML_TAG_CPPEXTENSIONS, "foo");
    xmlWriter.AddTag(XML_TAG_HEADEREXTENSIONS, "foo");
    xmlWriter.AddTag(XML_TAG_SOURCEENCODING, "foo");
    xmlWriter.AddTag(XML_TAG_MAKEDEPPROJECTS, "foo");

    // end data container
    xmlWriter.CloseTag(XML_TAG_DATA);

    // end configuration container
    xmlWriter.CloseTag(XML_TAG_CONFIGURATION);

    // end project container
    xmlWriter.CloseTag(XML_TAG_PROJECT);
  }

  void cmExtraNetBeans69Generator::CreateConfigurationFile(cmMakefile& makefile, const cmTarget& target) const {

    const string filename = GetOutputDirectory(makefile, target) + FILE_SEPARATOR + "configurations.xml";

    cmGeneratedFileStream fout(filename.c_str());
    if (!fout) {
      return;
    }
    cmXmlWriter xmlWriter(fout);

    map<string, string> attributes;

    // main configuration container (version 65 means NetBeans 6.5)?
    attributes.clear();
    attributes.insert(ATTRIBUTE("version", "65"));
    xmlWriter.OpenTag(XML_TAG_CONFIGURATIONDESCRIPTOR, attributes);

    // logical folder "root"
    attributes.clear();
    attributes.insert(ATTRIBUTE("name", "root"));
    attributes.insert(ATTRIBUTE("displayName", "root"));
    attributes.insert(ATTRIBUTE("projectFiles", "true"));
    xmlWriter.OpenTag(XML_TAG_LOGICALFOLDER, attributes);

    // add logical folders for source groups and their subgroups
    AddLogicalFolders(xmlWriter, makefile);

    // source root list
    xmlWriter.OpenTag(XML_TAG_SOURCEROOTLIST);

    // TODO: find source root list
    xmlWriter.AddTag(XML_TAG_ELEM, "foo");

    // end source root list
    xmlWriter.CloseTag(XML_TAG_SOURCEROOTLIST);

    // in this case the makefile is a predefined "dummy"
    xmlWriter.AddTag(XML_TAG_PROJECTMAKEFILE, "Makefile");

    // builds are
    string buildType = makefile.GetDefinition("CMAKE_BUILD_TYPE");

    // start of configuration sections ("Debug", "Release", etc)
    xmlWriter.OpenTag(XML_TAG_CONFS);

    // start of single configuration
    attributes.clear();
    attributes.insert(ATTRIBUTE("name", buildType));
    attributes.insert(ATTRIBUTE("type", "1"));
    xmlWriter.OpenTag(XML_TAG_CONF);

    // project specific tool chain settings
    xmlWriter.OpenTag(XML_TAG_TOOLSSET);
    xmlWriter.AddTag(XML_TAG_DEVELOPMENTSERVER, "foo");
    xmlWriter.AddTag(XML_TAG_COMPILERSET, "foo");
    xmlWriter.AddTag(XML_TAG_PLATFORM, "foo");

    // end project specific tool chain settings
    xmlWriter.CloseTag(XML_TAG_TOOLSSET);

    // build settings
    xmlWriter.OpenTag(XML_TAG_COMPILETYPE);

    // compiler settings
    xmlWriter.OpenTag(XML_TAG_CCTOOL);

    // include directories
    xmlWriter.OpenTag(XML_TAG_INCDIR);
    AddIncludePaths(xmlWriter, makefile);
    xmlWriter.CloseTag(XML_TAG_INCDIR);

    // compiler flags
    AddCompileFlags(xmlWriter, makefile);

    // warning level
    xmlWriter.AddTag(XML_TAG_WARNINGLEVEL, "foo");

    // end compiler settings
    xmlWriter.CloseTag(XML_TAG_CCTOOL);

    // Linker settings
    xmlWriter.OpenTag(XML_TAG_LINKERTOOL);

    // executable name
    xmlWriter.AddTag(XML_TAG_OUTPUT, "foo");

    // library paths
    xmlWriter.OpenTag(XML_TAG_LINKERADDLIB);

    xmlWriter.AddTag(XML_TAG_PELEM, "foo");

    // end library paths
    xmlWriter.CloseTag(XML_TAG_LINKERADDLIB);

    // runtime library paths
    xmlWriter.OpenTag(XML_TAG_LINKERDYNSERCH);

    xmlWriter.AddTag(XML_TAG_PELEM, "foo");

    // end runtime library paths
    xmlWriter.CloseTag(XML_TAG_LINKERDYNSERCH);

    // libraries
    xmlWriter.OpenTag(XML_TAG_LINKERLIBITEMS);

    xmlWriter.AddTag(XML_TAG_LINKERLIBLIBITEM, "foo");

    // end libraries
    xmlWriter.CloseTag(XML_TAG_LINKERLIBITEMS);

    // end linker settings
    xmlWriter.CloseTag(XML_TAG_LINKERTOOL);

    // end build settings
    xmlWriter.CloseTag(XML_TAG_COMPILETYPE);

    // end of single configuration
    xmlWriter.CloseTag(XML_TAG_CONF);

    // end of configuration sections
    xmlWriter.CloseTag(XML_TAG_CONFS);

    // end logical folder "root"
    xmlWriter.CloseTag(XML_TAG_LOGICALFOLDER);

    // end main configuration container
    xmlWriter.CloseTag(XML_TAG_CONFIGURATIONDESCRIPTOR);

  }

  void cmExtraNetBeans69Generator::AddCompileFlags(cmXmlWriter& xmlWriter, cmMakefile& makefile) const {

    string property = makefile.GetProperty("COMPILE_DEFINITIONS");

    // expand the list into a vector
    vector<string> definitions;
    cmSystemTools::ExpandListArgument(property, definitions);

    // concatenate the list
    stringstream out;
    for (vector<string>::const_iterator it = definitions.begin(); it != definitions.end();) {
      const string& definition = *it;
      out << "-D" << cmXMLSafe(definition);
      it++;
      if (it != definitions.end()) {
        out << " ";
      }
    }

    string buildType = makefile.GetDefinition("CMAKE_BUILD_TYPE");


    xmlWriter.AddTag(XML_TAG_COMMANDLINE, out.str());
  }

  void cmExtraNetBeans69Generator::AddIncludePaths(cmXmlWriter& xmlWriter, cmMakefile& makefile) const {

    const vector<string>& includeDirs = makefile.GetIncludeDirectories();

    for (vector<string>::const_iterator it = includeDirs.begin(); it != includeDirs.end(); ++it) {

      const string& includeDir = *it;

      if (!includeDir.empty()) {
        xmlWriter.AddTag(XML_TAG_PELEM, cmSystemTools::CollapseFullPath(it->c_str()));
      }
    }
  }

  void cmExtraNetBeans69Generator::AddLogicalFolders(cmXmlWriter& xmlWriter, cmMakefile& makefile) const {

    std::vector<cmSourceGroup> sourceGroups = makefile.GetSourceGroups();
    const std::vector<cmSourceFile*> sourceFiles = makefile.GetSourceFiles();

    // for each file find out in which source group it is supposed to be
    // and assign it to this source group (for some reason, the files
    // are not assigned to source groups initially).
    for (std::vector<cmSourceFile*>::const_iterator it1 = sourceFiles.begin(); it1 != sourceFiles.end(); it1++) {
      cmSourceFile& sourceFile = *(*it1);
      string sourceFilePath = sourceFile.GetFullPath();
      cmSourceGroup& sourceGroup = makefile.FindSourceGroup(sourceFilePath.c_str(), sourceGroups);
      sourceGroup.AssignSource(&sourceFile);
    }

    // add one logical folder per source group
    for (vector<cmSourceGroup>::const_iterator it1 = sourceGroups.begin(); it1 != sourceGroups.end(); it1++) {
      AddLogicalFolder(xmlWriter, *it1);
    }
  }

  void cmExtraNetBeans69Generator::AddLogicalFolder(cmXmlWriter& xmlWriter, const cmSourceGroup& sourceGroup) const {

    const string& groupName = sourceGroup.GetName();

    // sometimes there is an empty source group without a valid name
    if (groupName.empty()) {
      return;
    }

    // logical folder for this group
    map<string, string> attributes;
    attributes.insert(ATTRIBUTE("name", groupName));
    attributes.insert(ATTRIBUTE("displayName", groupName));
    attributes.insert(ATTRIBUTE("projectFiles", "true"));
    xmlWriter.OpenTag(XML_TAG_LOGICALFOLDER, attributes);

    // this group's source files
    const std::vector<const cmSourceFile*>& sourceFiles = sourceGroup.GetSourceFiles();
    for (std::vector<const cmSourceFile*>::const_iterator it2 = sourceFiles.begin(); it2 != sourceFiles.end(); it2++) {

      cmSourceFile sourceFile = *(*it2);
      const string& fileName = sourceFile.GetFullPath();
      xmlWriter.AddTag(XML_TAG_ITEMPATH, fileName);
    }

    // this group's child source groups
    const std::vector<cmSourceGroup>& children = sourceGroup.GetGroupChildren();
    for (vector<cmSourceGroup>::const_iterator it3 = children.begin(); it3 != children.end(); it3++) {
      const cmSourceGroup& child = *it3;
      AddLogicalFolder(xmlWriter, child);
    }

    // end logical folder for this group
    xmlWriter.CloseTag(XML_TAG_LOGICALFOLDER);
  }

  const char* cmExtraNetBeans69Generator::GetActualName() {
    return ACTUAL_NAME.c_str();
  }

  void cmExtraNetBeans69Generator::CreateProjectFolders(cmMakefile& makefile, const cmTarget& target) const {

    string projectDirectory = GetOutputDirectory(makefile, target);

    if (!cmSystemTools::MakeDirectory(projectDirectory.c_str())) {
      cmSystemTools::Error(
        "Error creating directory ", projectDirectory.c_str());
    }

    string netbeansDirectory =
      projectDirectory + FILE_SEPARATOR + NETBEANS_DIR;

    if (!cmSystemTools::MakeDirectory(netbeansDirectory.c_str())) {
      cmSystemTools::Error(
        "Error creating directory ", netbeansDirectory.c_str());
    }
  }

  string cmExtraNetBeans69Generator::GetOutputDirectory(cmMakefile& makefile, const cmTarget& target) const {
    return makefile.GetHomeOutputDirectory() + FILE_SEPARATOR + target.GetName();
  }
}
