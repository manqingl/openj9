/*[INCLUDE-IF Sidecar19-SE]*/
/*******************************************************************************
 * Copyright (c) 2016, 2020 IBM Corp. and others
 *
 * This program and the accompanying materials are made available under
 * the terms of the Eclipse Public License 2.0 which accompanies this
 * distribution and is available at https://www.eclipse.org/legal/epl-2.0/
 * or the Apache License, Version 2.0 which accompanies this distribution and
 * is available at https://www.apache.org/licenses/LICENSE-2.0.
 *
 * This Source Code may also be made available under the following
 * Secondary Licenses when the conditions for such availability set
 * forth in the Eclipse Public License, v. 2.0 are satisfied: GNU
 * General Public License, version 2 with the GNU Classpath
 * Exception [1] and GNU General Public License, version 2 with the
 * OpenJDK Assembly Exception [2].
 *
 * [1] https://www.gnu.org/software/classpath/license.html
 * [2] http://openjdk.java.net/legal/assembly-exception.html
 *
 * SPDX-License-Identifier: EPL-2.0 OR Apache-2.0 OR GPL-2.0 WITH Classpath-exception-2.0 OR LicenseRef-GPL-2.0 WITH Assembly-exception
 *******************************************************************************/

/**
 * Diagnostic Tool Framework for Java&trade; (DTFJ)
 *
 * The Diagnostic Tool Framework for Java&trade; (DTFJ) is a Java application
 * programming interface (API) used to support the building of Java diagnostic
 * tools. DTFJ works with data from a system dump or a Javadump.
 */
@SuppressWarnings("module")
module openj9.dtfj {
  requires transitive java.desktop;
  requires transitive java.logging;
  requires java.xml;
  requires openj9.traceformat;
  /*[IF PLATFORM-mz31 | PLATFORM-mz64]*/
  requires ibm.jzos;
  /*[ENDIF]*/
//Exporting all for service purpose.
 exports com.ibm.dtfj.addressspace;
 exports com.ibm.dtfj.binaryreaders;
 exports com.ibm.dtfj.corereaders;
 exports com.ibm.dtfj.corereaders.j9;
 exports com.ibm.dtfj.corereaders.zos.dumpreader;
 exports com.ibm.dtfj.corereaders.zos.le;
 exports com.ibm.dtfj.corereaders.zos.mvs;
 exports com.ibm.dtfj.corereaders.zos.util;
 exports com.ibm.dtfj.image;
 exports com.ibm.dtfj.image.j9;
 exports com.ibm.dtfj.image.j9.corrupt;
 exports com.ibm.dtfj.image.javacore;
 exports com.ibm.dtfj.java;
 exports com.ibm.dtfj.java.j9;
 exports com.ibm.dtfj.java.javacore;
 exports com.ibm.dtfj.javacore.builder;
 exports com.ibm.dtfj.javacore.builder.javacore;
 exports com.ibm.dtfj.javacore.parser.framework;
 exports com.ibm.dtfj.javacore.parser.framework.input;
 exports com.ibm.dtfj.javacore.parser.framework.parser;
 exports com.ibm.dtfj.javacore.parser.framework.scanner;
 exports com.ibm.dtfj.javacore.parser.framework.tag;
 exports com.ibm.dtfj.javacore.parser.j9;
 exports com.ibm.dtfj.javacore.parser.j9.registered;
 exports com.ibm.dtfj.javacore.parser.j9.section.classloader;
 exports com.ibm.dtfj.javacore.parser.j9.section.common;
 exports com.ibm.dtfj.javacore.parser.j9.section.environment;
 exports com.ibm.dtfj.javacore.parser.j9.section.memory;
 exports com.ibm.dtfj.javacore.parser.j9.section.monitor;
 exports com.ibm.dtfj.javacore.parser.j9.section.nativememory;
 exports com.ibm.dtfj.javacore.parser.j9.section.platform;
 exports com.ibm.dtfj.javacore.parser.j9.section.stack;
 exports com.ibm.dtfj.javacore.parser.j9.section.thread;
 exports com.ibm.dtfj.javacore.parser.j9.section.title;
 exports com.ibm.dtfj.phd;
 exports com.ibm.dtfj.phd.parser;
 exports com.ibm.dtfj.phd.util;
 exports com.ibm.dtfj.runtime;
 exports com.ibm.dtfj.utils;
 exports com.ibm.dtfj.utils.file;
 exports com.ibm.java.diagnostics.utils;
 exports com.ibm.java.diagnostics.utils.commands;
 exports com.ibm.java.diagnostics.utils.plugins;
 exports com.ibm.java.diagnostics.utils.plugins.impl;
 exports com.ibm.jvm.j9.dump.extract;
 exports com.ibm.jvm.j9.dump.indexsupport;
}
