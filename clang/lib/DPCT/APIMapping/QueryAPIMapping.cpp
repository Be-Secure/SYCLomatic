//===--------------- QueryAPIMapping.cpp ----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "QueryAPIMapping.h"

namespace clang {
namespace dpct {

std::unordered_map<std::string, std::string> APIMapping::EntryMap;

void APIMapping::registerEntry(const std::string &Name,
                               const std::string &Description) {
  if (Description == "NA")
    return;
  EntryMap[Name] = Description;
}

void APIMapping::initEntryMap() {
  static const std::string MultiStr =
      "\nThere are multi kinds of migrations for this API with different "
      "migration options,\nsuggest to use the tool to migrate a API usage "
      "code to see more detail of the migration.";
#define ENTRY(INTERFACENAME, APINAME, VALUE, FLAG, TARGET, COMMENT, MAPPING)   \
  registerEntry(#APINAME, MAPPING);
#define ENTRY_MEMBER_FUNCTION(INTERFACEOBJNAME, OBJNAME, INTERFACENAME, APINAME, VALUE, FLAG,    \
                              TARGET, COMMENT, MAPPING)                        \
  registerEntry(#OBJNAME "." #APINAME, MAPPING);
#define MAP_SYCL(MAPPING) MAPPING
#define MAP_DPCT(MAPPING) MAPPING
#define MAP_MULTI(MAPPING) MAPPING + MultiStr
#define MAP_DESC(MAPPING) MAPPING
#include "../APINames.inc"
#undef ENTRY_MEMBER_FUNCTION
#undef ENTRY
}

} // namespace dpct
} // namespace clang
