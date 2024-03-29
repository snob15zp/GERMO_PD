################################################################################
# \file build.mk
#
# \brief
# Performs the compilation and linking steps.
#
################################################################################
# \copyright
# Copyright 2018-2019 Cypress Semiconductor Corporation
# SPDX-License-Identifier: Apache-2.0
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
################################################################################

ifeq ($(WHICHFILE),true)
$(info Processing $(lastword $(MAKEFILE_LIST)))
endif


################################################################################
# Macros
################################################################################

#
# Construct recursive make for dependent lib apps
# 1: The name of the target
# 2: The lib app directory
#
define CY_MACRO_SHAREDLIB_DEPENDENCIES

$(1)_SED_PATTERN=$(subst /,\/,$(subst .,\.,$(2)))\/
ifeq ($(CY_BUILD_LOC),$(CY_APP_LOCATION)/build)
$(1)_SHAREDLIB_BUILD_LOCATION?=$(2)/build/$(TARGET)/$(CONFIG)
else
$(1)_SHAREDLIB_BUILD_LOCATION?=$(CY_PREBUILD_BUILD_LOC)/$(1)/$(TARGET)/$(CONFIG)
endif

# Dependencies
$$($(1)_SHAREDLIB_BUILD_LOCATION)/inclist.rsp: shared_libs
$$($(1)_SHAREDLIB_BUILD_LOCATION)/liblist.rsp: shared_libs
$$($(1)_SHAREDLIB_BUILD_LOCATION)/artifact.rsp: shared_libs
$(1)_shared_lib: | $$($(1)_SHAREDLIB_BUILD_LOCATION)/inclist.rsp
$(1)_shared_lib: | $$($(1)_SHAREDLIB_BUILD_LOCATION)/liblist.rsp
$(1)_shared_lib: | $$($(1)_SHAREDLIB_BUILD_LOCATION)/artifact.rsp

$(1)_shared_lib:
	$(CY_NOISE)touch $$($(1)_SHAREDLIB_BUILD_LOCATION)/inclist.rsp \
	$$($(1)_SHAREDLIB_BUILD_LOCATION)/liblist.rsp \
	$$($(1)_SHAREDLIB_BUILD_LOCATION)/artifact.rsp; \
	inclist_read=$$$$(cat $$($(1)_SHAREDLIB_BUILD_LOCATION)/inclist.rsp | sed -e "s/^-I/-I$$($(1)_SED_PATTERN)/g" | tr " " "\n"); \
	if [ -f "$$($(1)_SHAREDLIB_BUILD_LOCATION)/inclist_export.rsp" ]; then \
		inclist_export_read=$$$$(cat $$($(1)_SHAREDLIB_BUILD_LOCATION)/inclist_export.rsp | tr " " "\n"); \
		if [[ "$$$$inclist_read" != "$$$$inclist_export_read" ]]; then \
			echo "$$$$inclist_read" > $$($(1)_SHAREDLIB_BUILD_LOCATION)/inclist_export.rsp ;\
		fi; \
	else \
		echo "$$$$inclist_read" > $$($(1)_SHAREDLIB_BUILD_LOCATION)/inclist_export.rsp ;\
	fi;\
	liblist_read=$$$$(cat $$($(1)_SHAREDLIB_BUILD_LOCATION)/liblist.rsp | sed -e "s/^/$$($(1)_SED_PATTERN)/g" | tr " " "\n"); \
	if [ -f "$$($(1)_SHAREDLIB_BUILD_LOCATION)/liblist_export.rsp" ]; then \
		liblist_export_read=$$$$(cat $$($(1)_SHAREDLIB_BUILD_LOCATION)/liblist_export.rsp | tr " " "\n"); \
		if [[ "$$$$liblist_read" != "$$$$liblist_export_read" ]]; then \
			echo "$$$$liblist_read" > $$($(1)_SHAREDLIB_BUILD_LOCATION)/liblist_export.rsp ;\
		fi; \
	else \
		echo "$$$$liblist_read" > $$($(1)_SHAREDLIB_BUILD_LOCATION)/liblist_export.rsp ;\
	fi;\
	artifact_read=$$$$(sed '1s;^;$$($(1)_SHAREDLIB_BUILD_LOCATION)/;' $$($(1)_SHAREDLIB_BUILD_LOCATION)/artifact.rsp); \
	if [ -f "$$($(1)_SHAREDLIB_BUILD_LOCATION)/artifact_export.rsp" ]; then \
		artifact_export_read=$$$$(cat $$($(1)_SHAREDLIB_BUILD_LOCATION)/artifact_export.rsp); \
		if [[ "$$$$artifact_read" -nt "$(CY_PREBUILD_TARGET)" ]] || [[ "$$$$artifact_read" != "$$$$artifact_export_read" ]]; then\
			echo "$$$$artifact_read" > $$($(1)_SHAREDLIB_BUILD_LOCATION)/artifact_export.rsp;\
		fi; \
	else \
		echo "$$$$artifact_read" > $$($(1)_SHAREDLIB_BUILD_LOCATION)/artifact_export.rsp;\
	fi;

endef

#
# Construct recursive make for dependent apps
# 1: The name of the target
# 2: The dependent app directory
#
define CY_MACRO_DEPENDENT_APPS

$(1)_SED_PATTERN=$(subst /,\/,$(subst .,\.,$(2)))
ifeq ($(CY_BUILD_LOC),$(CY_APP_LOCATION)/build)
$(1)_DEPAPP_BUILD_LOCATION?=$(2)/build/$(TARGET)/$(CONFIG)
else
$(1)_DEPAPP_BUILD_LOCATION?=$(CY_PREBUILD_BUILD_LOC)/$(1)/$(TARGET)/$(CONFIG)
endif

# Dependencies
$$($(1)_DEPAPP_BUILD_LOCATION)/artifact.rsp: $(1)_dependent_app
$(1)_dependent_postbuild: | $$($(1)_DEPAPP_BUILD_LOCATION)/artifact.rsp

$(1)_dependent_app: | dependent_apps_preprint
	$$(info )
	$$(info ==============================================================================)
	$$(info = Dependent app $(1) =)
	$$(info ==============================================================================)
	$(CY_NOISE)$(CY_DEPAPP_MAKECMD) $(2)
ifneq ($(CY_DEPAPP_CLEAN),1)
	$(CY_NOISE)touch $$($(1)_DEPAPP_BUILD_LOCATION)/artifact.rsp; \
	artifact_elf=$$$$(sed '1s;^;$$($(1)_DEPAPP_BUILD_LOCATION)/;' $$($(1)_DEPAPP_BUILD_LOCATION)/artifact.rsp); \
	artifact_bare=$$$${artifact_elf%.$(CY_TOOLCHAIN_SUFFIX_TARGET)}; \
	artifact_bin=$$$$artifact_bare.bin; \
	artifact_c=$$$$artifact_bare.c; \
	artifact_name=$$$${artifact_bare##*/}; \
	if [[ "$$$$artifact_elf" == *.$(CY_TOOLCHAIN_SUFFIX_TARGET) ]]; then \
		if [[ "$$$$artifact_elf" -nt "$(CY_PREBUILD_TARGET)" ]] || [[ ! -f "$$$$artifact_bin" ]] || [[ ! -f "$$$$artifact_elf" ]] || [[ ! -f "$$$$artifact_c" ]]; then\
			$(call CY_MACRO_ELF2BIN,"$$$$artifact_elf","$$$$artifact_bin");\
			$(CY_BASELIB_CORE_PATH)/make/scripts/bin2c.pl "$$$$artifact_name" "$$$$artifact_bin" > "$$$$artifact_c"; \
			echo "$$$$artifact_c" > $$($(1)_DEPAPP_BUILD_LOCATION)/artifact_export.rsp;\
		fi; \
	fi;
endif
	$(CY_NOISE)echo ==============================================================================

endef


################################################################################
# Defines
################################################################################

# Define application target
CY_PREBUILD_TARGET=$(CY_CONFIG_DIR)/$(APPNAME).$(CY_TOOLCHAIN_SUFFIX_TARGET)

################################################################################
# Shared libs post-processing
################################################################################

ifneq ($(SEARCH_LIBS_AND_INCLUDES),)

# Construct shared libs targets for all dependent lib apps
$(foreach lib,$(SEARCH_LIBS_AND_INCLUDES),$(eval $(call CY_MACRO_SHAREDLIB_DEPENDENCIES,$(notdir $(lib)),$(lib))))

CY_SHAREDLIB_LIST=$(foreach lib,$(SEARCH_LIBS_AND_INCLUDES),$(notdir $(lib)_shared_lib))
CY_SHAREDLIB_BUILD_LOCATIONS=$(foreach lib,$(SEARCH_LIBS_AND_INCLUDES),\
								$(notdir $(lib))_SHAREDLIB_BUILD_LOCATION=$($(notdir $(lib))_SHAREDLIB_BUILD_LOCATION))

endif


################################################################################
# Dependent apps post-processing
################################################################################

ifneq ($(DEPENDENT_APP_PATHS),)

# Skip the postprocessing if it's the clean target
ifeq ($(filter clean,$(MAKECMDGOALS)),clean)
CY_DEPAPP_CLEAN=1
endif

# Skip the programming steps only for dependent apps when a project name is not set
ifeq ($(CY_IDE_PRJNAME),) 
CY_DEPAPP_MAKECMDGOALS=$(strip $(subst program,build,\
						$(subst qprogram,,\
						$(subst debug,build,\
						$(subst qdebug,,\
						$(MAKECMDGOALS))))))
else
# Skip the programming steps and export configurations generation for dependent apps when a project name is set
CY_DEPAPP_MAKECMDGOALS=$(strip $(subst program,build,\
						$(subst qprogram,,\
						$(subst debug,build,\
						$(subst qdebug,,\
						$(subst eclipse,,\
						$(subst ewarm8,,\
						$(subst uvision5,,\
						$(subst vscode,,\
						$(MAKECMDGOALS))))))))))
endif

# Construct the make command (arguments are necessary for locating the build output directory)
ifeq ($(CY_DEPAPP_MAKECMDGOALS),)
CY_DEPAPP_MAKECMD=echo Nothing to be done for
else
CY_DEPAPP_MAKECMD=+ $(MAKE) $(CY_DEPAPP_MAKECMDGOALS) TOOLCHAIN=$(TOOLCHAIN) TARGET=$(TARGET) CONFIG=$(CONFIG) --no-print-directory -C
endif

# Construct dependent app targets for post-processing
$(foreach app,$(DEPENDENT_APP_PATHS),$(eval $(call CY_MACRO_DEPENDENT_APPS,$(notdir $(app)),$(app))))

CY_DEPAPP_LIST=$(foreach app,$(DEPENDENT_APP_PATHS),$(notdir $(app)_dependent_app))
CY_DEPAPP_BUILD_LOCATIONS=$(foreach app,$(DEPENDENT_APP_PATHS),\
								$(notdir $(app))_DEPAPP_BUILD_LOCATION=$($(notdir $(app))_DEPAPP_BUILD_LOCATION))

dependent_apps_preprint:
	$(CY_NOISE)echo Building dependent apps

dependent_apps: $(CY_DEPAPP_LIST)
	$(CY_NOISE)echo; echo Dependent apps build complete

else

# Expty on purpose
dependent_apps:

endif


################################################################################
# Configurators
################################################################################

# Add the dependency to configurator code generation ("override CY_PREBUILD_GEN_CONFIG=" to manually skip)
CY_PREBUILD_GEN_CONFIG=gen_config
# Note: configurators cannot be run in parallel. Therefore linearize using dependencies
$(CY_CONFIG_MODUS_FILE) $(CY_CONFIG_CYBT_FILE) $(CY_CONFIG_CYUSBDEV_FILE) $(CY_CONFIG_MTBEZPD_FILE) $(CY_CONFIG_MTBLIN_FILE) : shared_libs $(CY_SHAREDLIB_LIST) dependent_apps

################################################################################
# Targets
################################################################################

#
# Top-level prebuild dependency
#
prebuild: CY_PREBUILD_postprint

CY_PREBUILD_dependencies: shared_libs $(CY_SHAREDLIB_LIST) dependent_apps $(CY_PREBUILD_GEN_CONFIG)

#
# Create the output directory in case prebuilds require it
#
CY_PREBUILD_mkdirs: CY_PREBUILD_dependencies
	$(CY_NOISE)echo; \
	mkdir -p $(CY_CONFIG_DIR) $(CY_CMD_TERM)

#
# Run BSP prebuild step
#
CY_PREBUILD_bsp_prebuild: CY_PREBUILD_mkdirs
	$(CY_BSP_PREBUILD)

#
# Run application prebuild step
#
CY_PREBUILD_app_prebuild: CY_PREBUILD_bsp_prebuild
	$(PREBUILD)

#
# Run recipe prebuild step
#
CY_PREBUILD_prebuild: CY_PREBUILD_app_prebuild
	$(CY_NOISE)$(CY_RECIPE_PREBUILD) $(CY_CMD_TERM)

#
# Prebuild postprint and dependency ordering
#
CY_PREBUILD_postprint: CY_PREBUILD_prebuild
	$(CY_NOISE)echo "Prebuild operations complete"

#
# Indicate all phony targets that should be built regardless
#
.PHONY: prebuild gen_config $(CY_SHAREDLIB_LIST) shared_libs $(CY_DEPAPP_LIST) dependent_apps
.PHONY: CY_PREBUILD_dependencies CY_PREBUILD_mkdirs CY_PREBUILD_postprint
.PHONY: CY_PREBUILD_prebuild CY_PREBUILD_app_prebuild CY_PREBUILD_bsp_prebuild
