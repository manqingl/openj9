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
 * Defines the jdmpview tool for reading system core and java core diagnostic files.
 */
@SuppressWarnings("module")
module openj9.dtfjview {
  requires openj9.dtfj;
  requires java.logging;
  
//Exporting all for service purpose.
 exports com.ibm.jvm.dtfjview;
 exports com.ibm.jvm.dtfjview.commands;
 exports com.ibm.jvm.dtfjview.commands.helpers;
 exports com.ibm.jvm.dtfjview.commands.infocommands;
 exports com.ibm.jvm.dtfjview.commands.setcommands;
 exports com.ibm.jvm.dtfjview.commands.showcommands;
 exports com.ibm.jvm.dtfjview.commands.xcommands;
 exports com.ibm.jvm.dtfjview.heapdump;
 exports com.ibm.jvm.dtfjview.heapdump.classic;
 exports com.ibm.jvm.dtfjview.heapdump.portable;
 exports com.ibm.jvm.dtfjview.spi;
 exports com.ibm.jvm.dtfjview.tools;
 exports com.ibm.jvm.dtfjview.tools.impl;
 exports com.ibm.jvm.dtfjview.tools.utils;

}
