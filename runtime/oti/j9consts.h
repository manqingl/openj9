/*******************************************************************************
 * Copyright (c) 1991, 2020 IBM Corp. and others
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

#ifndef J9CONSTS_H
#define J9CONSTS_H

/* @ddr_namespace: map_to_type=J9Consts */

#include "j9cfg.h"
#include "j9comp.h"
#include "omrgcconsts.h"

#ifdef __cplusplus
extern "C" {
#endif

/* NOTE: Constants in this file which are read by DDR must be numeric, not calculated.
 * Comments on the constants indicate how they were computed.
 */

#define J9_EVENT_SOM_VALUE UDATA_MAX

#define J9_RUNTIME_STACK_FILL 0xDEADFACE

/* 8 * sizeof(UDATA) */
#if defined(J9VM_ENV_DATA64)
#define J9_OBJECT_DESCRIPTION_SIZE 64
#else /* J9VM_ENV_DATA64 */
#define J9_OBJECT_DESCRIPTION_SIZE 32
#endif /* J9VM_ENV_DATA64 */

/* The high bit of a UDATA */
#define J9_JNI_MID_INTERFACE ((UDATA)IDATA_MIN)

#define J9_REQUIRED_CLASS_SHIFT 0x8
#define J9_REQUIRED_CLASS_ALIGNMENT 0x100 /* (1 << J9_REQUIRED_CLASS_SHIFT) */

#define J9_INLINE_JNI_MAX_ARG_COUNT 0x20

#define J9_JIT_RETURN_TYPES_SIZE 0x6

/* Java stack layout:
 *	A - J9JavaStack struct header
 *	B - space reserved for signal handling on the java stack
 *	C - space reserved for unchecked access during StackOverflowError construction
 *		<fatal stack overflow if below here when constructing StackOverflowError>
 *	D - space reserved for checked access during StackOverflowError construction
 *		<stackOverflowMark is here>
 *	E - normal stack area
 *
 *	Base reserved size is 1K.  Add another 3K on x86 platforms (signal handlers may run on
 *	the java stack temporarily due to ESP re-use).  Double that value on 64-bit targets.
 *
 *	Overflow size is the above plus another 1K (2K on 64-bit).
 */
#if defined(J9VM_ENV_DATA64)
#if defined(J9VM_ARCH_X86)
#define J9_STACK_OVERFLOW_RESERVED_SIZE 0x2000
#define J9_STACK_OVERFLOW_AND_HEADER_SIZE 0x2800
#else /* J9VM_ARCH_X86 */
#define J9_STACK_OVERFLOW_RESERVED_SIZE 0x800
#define J9_STACK_OVERFLOW_AND_HEADER_SIZE 0x1000
#endif /* J9VM_ARCH_X86 */
#else /* J9VM_ENV_DATA64 */
#if defined(J9VM_ARCH_X86)
#define J9_STACK_OVERFLOW_RESERVED_SIZE 0x1000
#define J9_STACK_OVERFLOW_AND_HEADER_SIZE 0x1400
#else /* J9VM_ARCH_X86 */
#define J9_STACK_OVERFLOW_RESERVED_SIZE 0x400
#define J9_STACK_OVERFLOW_AND_HEADER_SIZE 0x800
#endif /* J9VM_ARCH_X86 */
#endif /* J9VM_ENV_DATA64 */

/* The maximum number of bytes allowed in the data portion of an array object.  This value must be
 * small enough that adding the header size and any other non-arrayoid overhead (such as the alignment
 * value for keeping objects aligned) can not overflow a UDATA.
 *
 * For now, make this (UDATA_MAX+1) - 1K.  That's certainly enough to prevent the overflow, as the header
 * overhead will never be 1K.  It's also large enough that this will not impact the practical upper
 * bound on array element sizes, as the VM overhead will certainly be more than 1K.
 */
#define J9_MAXIMUM_INDEXABLE_DATA_SIZE ((UDATA)-1024)

#define J9_SUN_STATIC_FIELD_OFFSET_TAG 0x1
#define J9_SUN_FINAL_FIELD_OFFSET_TAG 0x2
#define J9_SUN_FIELD_OFFSET_MASK 0x3

#define J9_SIGBYTE_SIG_BEGIN 0x28
#define J9_SIGBYTE_SIG_END 0x29
#define J9_SIGBYTE_OBJECT_END 0x3B
#define J9_SIGBYTE_BYTE 0x42
#define J9_SIGBYTE_CHAR 0x43
#define J9_SIGBYTE_DOUBLE 0x44
#define J9_SIGBYTE_FLOAT 0x46
#define J9_SIGBYTE_INT 0x49
#define J9_SIGBYTE_LONG 0x4A
#define J9_SIGBYTE_OBJECT 0x4C
#define J9_SIGBYTE_SHORT 0x53
#define J9_SIGBYTE_VOID 0x56
#define J9_SIGBYTE_BOOLEAN 0x5A
#define J9_SIGBYTE_ARRAY 0x5B

#define J9_EX_CTOR_STRING 0x0
#define J9_EX_CTOR_INT 0x10000
#define J9_EX_CTOR_CLASS 0x20000
#define J9_EX_CTOR_CLASS_CLASS 0x30000
#define J9_EX_CTOR_THROWABLE 0x40000
#define J9_EX_CTOR_TYPE_MASK 0xFF0000

#define J9_EX_OOM_SHIFT 0x18
#define J9_EX_OOM_THREAD 0x1000000
#define J9_EX_OOM_OS_HEAP 0x2000000
#define J9_EX_OOM_JAVA_HEAP 0x4000000
#define J9_EX_OOM_TYPE_MASK 0xFF000000

#define J9_EXCEPTION_INDEX_SHIFT 0x10
#define J9_EXCEPTION_INDEX_MASK 0xFFFF

#define J9_NATIVE_METHOD_BIND_OUT_OF_MEMORY 0x1
#define J9_NATIVE_METHOD_BIND_ALLOW_JNI 0x1
#define J9_NATIVE_METHOD_BIND_SUCCESS 0x2
#define J9_NATIVE_METHOD_BIND_CAN_RUN_JAVA_CODE 0x2
#define J9_NATIVE_METHOD_BIND_FAIL 0x3
#define J9_NATIVE_METHOD_BIND_RECURSIVE 0x4

#define J9_PRIVATE_FLAGS_STACK_OVERFLOW 0x1
#define J9_PRIVATE_FLAGS_DAEMON_THREAD 0x2
#define J9_PRIVATE_FLAGS_FREE_OS_THREAD 0x4
#define J9_PRIVATE_FLAGS_ATTACHED_THREAD 0x8
#define J9_PRIVATE_FLAGS_SYSTEM_THREAD 0x10
#define J9_PRIVATE_FLAGS_CLOAD_NO_MEM 0x20
#define J9_PRIVATE_FLAGS_SCAV 0x40
#define J9_PRIVATE_FLAGS_LOADING_KNOWN_CLASS 0x80
#define J9_PRIVATE_FLAGS_CLOAD_OR_LINKING_OVERFLOW 0x100
#define J9_PRIVATE_FLAGS_IN_RESOLVE 0x200
#define J9_PRIVATE_FLAGS_CONSTRUCTING_EXCEPTION 0x400
#define J9_PRIVATE_FLAGS_FINALIZE_WORKER 0x800
#define J9_PRIVATE_FLAGS_NO_OBJECT 0x1000
#define J9_PRIVATE_FLAGS_OUT_OF_MEMORY 0x2000
#define J9_PRIVATE_FLAGS_FILL_EXISTING_TRACE 0x4000
#define J9_PRIVATE_FLAGS_REPORT_EXCEPTION_THROW 0x8000
#define J9_PRIVATE_FLAGS_REALTIME_THREAD 0x10000
#define J9_PRIVATE_FLAGS_UNUSED 0x20000
#define J9_PRIVATE_FLAGS_STACK_CORRUPT 0x40000
#define J9_PRIVATE_FLAGS_CONCURRENT_MARK_ACTIVE 0x100000
#define J9_PRIVATE_FLAGS_USE_BOOTSTRAP_LOADER 0x200000
#define J9_PRIVATE_FLAGS_NO_EXCEPTION_IN_START_JAVA_THREAD 0x400000
#define J9_PRIVATE_FLAGS_GC_MAIN_THREAD 0x800000
#define J9_PRIVATE_FLAGS_OSR_IN_PROGRESS 0x1000000
#define J9_PRIVATE_FLAGS_WALKED_FOR_CCR 0x2000000
#define J9_PRIVATE_FLAGS_SKIP_THREAD_SIGNAL_PROTECTION 0x4000000
#define J9_PRIVATE_FLAGS_FAILED_LOADING_REQUIRED_CLASS 0x8000000
#define J9_PRIVATE_FLAGS_REPORT_ERROR_LOADING_CLASS 0x10000000
#define J9_PRIVATE_FLAGS_RI_INITIALIZED 0x20000000
#define J9_PRIVATE_FLAGS_STACKS_OUT_OF_SYNC 0x40000000
#define J9_PRIVATE_FLAGS_FINAL_CALL_OUT_OF_MEMORY 0x80000000

#define J9_PRIVATE_FLAGS2_IN_SHARED_CACHE_READ_MUTEX  0x1
#define J9_PRIVATE_FLAGS2_CHECK_PACKAGE_ACCESS 0x2
#define J9_PRIVATE_FLAGS2_UNSAFE_HANDLE_SIGBUS 0x4
#define J9_PRIVATE_FLAGS2_RESTORE_MAINTHREAD 0x8

#define J9_PUBLIC_FLAGS_HALT_THREAD_EXCLUSIVE 0x1
#define J9_PUBLIC_FLAGS_DEBUG_VM_ACCESS 0x2
#define J9_PUBLIC_FLAGS_HALT_THREAD_JAVA_SUSPEND 0x4
#define J9_PUBLIC_FLAGS_DISABLE_INLINE_VM_ACCESS 0x8
#define J9_PUBLIC_FLAGS_STOP 0x10
#define J9_PUBLIC_FLAGS_VM_ACCESS 0x20
#define J9_PUBLIC_FLAGS_STOPPED 0x40
#define J9_PUBLIC_FLAGS_NOT_COUNTED_BY_EXCLUSIVE 0x80
#define J9_PUBLIC_FLAGS_THREAD_WAITING 0x100
#define J9_PUBLIC_FLAGS_THREAD_BLOCKED 0x200
#define J9_PUBLIC_FLAGS_THREAD_SLEEPING 0x400
#define J9_PUBLIC_FLAGS_REQUEST_SAFE_POINT 0x800
#define J9_PUBLIC_FLAGS_NOT_AT_SAFE_POINT 0x1000
#define J9_PUBLIC_FLAGS_HALTED_AT_SAFE_POINT 0x2000
#define J9_PUBLIC_FLAGS_NOT_COUNTED_BY_SAFE_POINT 0x4000
#define J9_PUBLIC_FLAGS_HALT_THREAD_INSPECTION 0x8000
#define J9_PUBLIC_FLAGS_THREAD_PARKED 0x20000
#define J9_PUBLIC_FLAGS_THREAD_TIMED 0x80000
#define J9_PUBLIC_FLAGS_JNI_CRITICAL_REGION 0x400000
#define J9_PUBLIC_FLAGS_POP_FRAMES_INTERRUPT 0x800000
#define J9_PUBLIC_FLAGS_JNI_CRITICAL_ACCESS 0x40000000
#define J9_PUBLIC_FLAGS_QUEUED_FOR_EXCLUSIVE 0x80000000

#define J9_PUBLIC_FLAGS_HALT_THREAD_SUSPEND_ANY J9_PUBLIC_FLAGS_HALT_THREAD_JAVA_SUSPEND
#define J9_PUBLIC_FLAGS_HALT_THREAD_ANY_NO_JAVA_SUSPEND (J9_PUBLIC_FLAGS_HALT_THREAD_INSPECTION | J9_PUBLIC_FLAGS_HALT_THREAD_EXCLUSIVE | J9_PUBLIC_FLAGS_HALTED_AT_SAFE_POINT)
#define J9_PUBLIC_FLAGS_HALT_THREAD_ANY (J9_PUBLIC_FLAGS_HALT_THREAD_ANY_NO_JAVA_SUSPEND | J9_PUBLIC_FLAGS_HALT_THREAD_SUSPEND_ANY)
#define J9_PUBLIC_FLAGS_HALT_VM_DUTIES J9_PUBLIC_FLAGS_HALT_THREAD_ANY
#define J9_PUBLIC_FLAGS_EXCLUSIVE_RESPONSE_MASK (J9_PUBLIC_FLAGS_HALT_THREAD_EXCLUSIVE | J9_PUBLIC_FLAGS_REQUEST_SAFE_POINT)
#define J9_PUBLIC_FLAGS_RELEASE_ACCESS_REQUIRED_MASK (J9_PUBLIC_FLAGS_HALT_THREAD_ANY | J9_PUBLIC_FLAGS_REQUEST_SAFE_POINT)
#define J9_PUBLIC_FLAGS_VMACCESS_ACQUIRE_BITS J9_PUBLIC_FLAGS_VM_ACCESS
#define J9_PUBLIC_FLAGS_VMACCESS_RELEASE_BITS (J9_PUBLIC_FLAGS_RELEASE_ACCESS_REQUIRED_MASK | J9_PUBLIC_FLAGS_DEBUG_VM_ACCESS | J9_PUBLIC_FLAGS_DISABLE_INLINE_VM_ACCESS)
#define J9_PUBLIC_FLAGS_VMACCESS_OUTOFLINE_MASK (J9_PUBLIC_FLAGS_HALT_THREAD_ANY | J9_PUBLIC_FLAGS_DEBUG_VM_ACCESS | J9_PUBLIC_FLAGS_DISABLE_INLINE_VM_ACCESS)

#define J9_METHOD_ENTER_PROFILER 0x2
#define J9_METHOD_ENTER_DEBUG_METHOD_ENTER 0x4
#define J9_METHOD_ENTER_DEBUG_FRAME_BUILD 0x8
#define J9_METHOD_ENTER_RASTRACE 0x10
#define J9_METHOD_ENTER_NEW_HOOK_INTERFACE 0x20

#define J9_JIT_QUEUED_FOR_COMPILATION -5
#define J9_JIT_NEVER_TRANSLATE -3
#define J9_JIT_RESOLVE_FAIL_COMPILE -2
#define J9_JIT_DCE_EXCEPTION_INFO 0x1
#define J9_JIT_TRANSITION_METHOD_ENTER 0x1
#define J9_JIT_TOGGLE_RI_ON_TRANSITION 0x1
#define J9_JIT_DCE_STACK_ATLAS 0x2
#define J9_JIT_TRANSITION_METHOD_EXIT 0x2
#define J9_JIT_TOGGLE_RI_IN_COMPILED_CODE 0x2
#define J9_JIT_DCE_RELOCATION_DATA 0x4
#define J9_JIT_DCE_THUNK_MAPPING_LIST 0x8
#define J9_JIT_DCE_THUNK_MAPPING 0x10
#define J9_JIT_DCE_HASH_TABLE 0x20
#define J9_JIT_DCE_MCC_HT_ENTRY 0x40
#define J9_JIT_DCE_AOT_METHOD_HEADER 0x80
#define J9_JIT_DCE_UNALLOCATED 0x100
#define J9_JIT_DCE_IN_USE 0x200
#define J9_JIT_DCE_AOT_PERSISTENT_INFO 0x400
#define J9_JIT_METADATA_HAS_BYTECODE_PC 0x4000
#define J9_JIT_METADATA_WIDE_EXCEPTIONS 0x8000

#define J9_RESOLVE_FLAG_RUNTIME_RESOLVE 0x0
#define J9_RESOLVE_FLAG_INIT_CLASS 0x1
#define J9_RESOLVE_FLAG_UNUSED_0x2 0x2
#define J9_RESOLVE_FLAG_NO_THROW_ON_FAIL 0x4
#define J9_RESOLVE_FLAG_JIT_COMPILE_TIME 0x8
#define J9_RESOLVE_FLAG_FIELD_SETTER 0x10
#define J9_RESOLVE_FLAG_CHECK_CLINIT 0x20
#define J9_RESOLVE_FLAG_INSTANTIABLE 0x40
#define J9_RESOLVE_FLAG_UNUSED_FLAG1 0x80 /* This bit is available for re-use */
#define J9_RESOLVE_FLAG_JCL_CONSTANT_POOL 0x100
#define J9_RESOLVE_FLAG_REDEFINE_CLASS 0x200
#define J9_RESOLVE_FLAG_NO_CLASS_INIT 0x400
#if defined(J9VM_OPT_VALHALLA_VALUE_TYPES)
#define J9_RESOLVE_FLAG_WITH_FIELD 0x800
#endif /* defined(J9VM_OPT_VALHALLA_VALUE_TYPES) */

#define J9_RESOLVE_STATIC_FIELD_TAG_FROM_CLINIT 0x1
#define J9_RESOLVE_STATIC_FIELD_TAG_IS_ISOLATED 0x2

#define J9_RUNTIME_REPORT_STACK_USE 0x1
#define J9_RUNTIME_VERIFY 0x2
#define J9_RUNTIME_INITIALIZED 0x4
#define J9_RUNTIME_JAVA_BASE_MODULE_CREATED 0x8
#define J9_RUNTIME_ALWAYS_COPY_JNI_CRITICAL 0x10
#define J9_RUNTIME_JIT_ACTIVE 0x20
#define J9_RUNTIME_CLEANUP 0x40

/* Determines whether the java/lang/String.value has [B or [C signature */
#define J9_RUNTIME_STRING_BYTE_ARRAY 0x80

#define J9_RUNTIME_SHUTDOWN 0x100
#define J9_RUNTIME_XFUTURE 0x200
#define J9_RUNTIME_PAINT_STACK 0x400
#define J9_RUNTIME_AOT_STRIPPED 0x800
#define J9_RUNTIME_SNIFF_AND_WHACK 0x1000
#define J9_RUNTIME_ARGENCODING_UNICODE 0x2000
#define J9_RUNTIME_ARGENCODING_LATIN 0x4000
#define J9_RUNTIME_ARGENCODING_UTF8 0x8000
#define J9_RUNTIME_DENY_ILLEGAL_ACCESS 0x10000
#define J9_RUNTIME_AGGRESSIVE 0x100000
#define J9_RUNTIME_EXTENDED_METHOD_BLOCK 0x200000
#define J9_RUNTIME_SHUTDOWN_STARTED 0x400000
#define J9_RUNTIME_EXIT_STARTED 0x800000
#define J9_RUNTIME_AGGRESSIVE_VERIFICATION 0x1000000
#define J9_RUNTIME_NO_PRIORITIES 0x2000000
#define J9_RUNTIME_DFPBD 0x4000000
#define J9_RUNTIME_DISABLE_VM_SHUTDOWN 0x8000000
#define J9_RUNTIME_ALWAYS_SPLIT_BYTECODES 0x10000000
#define J9_RUNTIME_OMIT_STACK_TRACES 0x20000000
#define J9_RUNTIME_SHOW_VERSION 0x40000000
#define J9_RUNTIME_TUNE_VIRTUALIZED 0x80000000

#define J9_EXTENDED_RUNTIME_USE_VECTOR_REGISTERS 0x1
#define J9_EXTENDED_RUNTIME_ENABLE_CPU_MONITOR	0x2
#define J9_EXTENDED_RUNTIME_ALWAYS_USE_JNI_CRITICAL 0x4
#define J9_EXTENDED_RUNTIME_ALLOW_CONTENDED_FIELDS 0x8
#define J9_EXTENDED_RUNTIME_RESTRICT_IFA 0x10
#define J9_EXTENDED_RUNTIME_FLAG_JSCRATCH_ADV_ON_FREE 0x20
#define J9_EXTENDED_RUNTIME_CHECK_DEBUG_INFO_COMPRESSION 0x40
#define J9_EXTENDED_RUNTIME_USER_REALTIME_ACCESS_BARRIER 0x80
#define J9_EXTENDED_RUNTIME_USE_J9JIMAGE_READER 0x100
#define J9_EXTENDED_RUNTIME_DEBUG_VM_ACCESS 0x200
#define J9_EXTENDED_RUNTIME_ENABLE_HCR 0x400
#define J9_EXTENDED_RUNTIME_I2J_MH_TRANSITION_ENABLED 0x800
#define J9_EXTENDED_RUNTIME_OSR_SAFE_POINT 0x1000
#define J9_EXTENDED_RUNTIME_SET_HW_PREFETCH 0x2000
#define J9_EXTENDED_RUNTIME_DEBUG_MODE 0x4000
#define J9_EXTENDED_RUNTIME_LAZY_SYMBOL_RESOLUTION 0x8000
#define J9_EXTENDED_RUNTIME_CLASSLOADER_LOCKING_ENABLED 0x10000
#define J9_EXTENDED_RUNTIME_PAGE_ALIGN_DIRECT_MEMORY 0x20000
#define J9_EXTENDED_RUNTIME_FAST_CLASS_HASH_TABLE 0x40000
#define J9_EXTENDED_RUNTIME_OSR_SAFE_POINT_FV 0x80000
#define J9_EXTENDED_RUNTIME_METHOD_TRACE_ENABLED 0x100000
#define J9_EXTENDED_RUNTIME_FOUND_JAVA_ASSERT_OPTION 0x200000
#define J9_EXTENDED_RUNTIME_ALLOW_NON_VIRTUAL_CALLS 0x400000
#define J9_EXTENDED_RUNTIME_POSITIVE_HASHCODE 0x800000
#define J9_EXTENDED_RUNTIME_CLASS_OBJECT_ASSIGNED 0x1000000
#define J9_EXTENDED_RUNTIME_FORCE_CLASSFILE_AS_INTERMEDIATE_DATA 0x2000000
#define J9_EXTENDED_RUNTIME_RECREATE_CLASSFILE_ONLOAD 0x4000000
#define J9_EXTENDED_RUNTIME_ALLOW_APPLICATION_CONTENDED_FIELDS 0x8000000
#define J9_EXTENDED_RUNTIME_HANDLE_SIGXFSZ 0x10000000
#define J9_EXTENDED_RUNTIME_DISABLE_FAST_CLASS_HASH_TABLE 0x20000000
#define J9_EXTENDED_RUNTIME_JIT_INLINE_WATCHES 0x40000000
#define J9_EXTENDED_RUNTIME_REDUCE_CPU_MONITOR_OVERHEAD 0x80000000

/* constants for J9JavaVM.extendedRuntimeFlags2 */
#define J9_EXTENDED_RUNTIME2_ENABLE_VALHALLA 0x1
#define J9_EXTENDED_RUNTIME2_COMPRESS_OBJECT_REFERENCES 0x2
#define J9_EXTENDED_RUNTIME2_ENABLE_PREVIEW 0x4
#define J9_EXTENDED_RUNTIME2_LOAD_AGENT_MODULE 0x8
#define J9_EXTENDED_RUNTIME2_ENABLE_DEEPSCAN 0x10
#define J9_EXTENDED_RUNTIME2_ENABLE_CLASS_RELATIONSHIP_VERIFIER 0x20
#define J9_EXTENDED_RUNTIME2_ENABLE_START_JITSERVER 0x40
#define J9_EXTENDED_RUNTIME2_ENABLE_VT_ARRAY_FLATTENING 0x80
#define J9_EXTENDED_RUNTIME2_SHOW_EXTENDED_NPEMSG 0x100
#define J9_EXTENDED_RUNTIME2_ENABLE_PORTABLE_SHARED_CACHE 0x200
#define J9_EXTENDED_RUNTIME2_ENABLE_AOT 0x400
#define J9_EXTENDED_RUNTIME2_LEGACY_MANGLING 0x800
#define J9_EXTENDED_RUNTIME2_VALUE_BASED_EXCEPTION 0x1000
#define J9_EXTENDED_RUNTIME2_VALUE_BASED_WARNING 0x2000
#define J9_EXTENDED_RUNTIME2_RAMSTATE_SNAPSHOT_RUN 0x4000
#define J9_EXTENDED_RUNTIME2_RAMSTATE_RESTORE_RUN 0x8000
#define J9_EXTENDED_RUNTIME2_SNAPSHOT_STATE_IS_RESTORED 0x10000
#define J9_EXTENDED_RUNTIME2_SNAPSHOT_STATE_SNAPSHOT_TRIGGERED 0x20000

/* TODO: Define this until the JIT removes it */
#define J9_EXTENDED_RUNTIME_ALLOW_GET_CALLER_CLASS 0

#define J9_OBJECT_HEADER_AGE_DEFAULT 0xA /* OBJECT_HEADER_AGE_DEFAULT */
#define J9_OBJECT_HEADER_SHAPE_MASK 0xE /* OBJECT_HEADER_SHAPE_MASK */
#define J9_OBJECT_HEADER_REMEMBERED_BITS_TO_SET 0x10 /* OBJECT_HEADER_LOWEST_REMEMBERED */
#define J9_OBJECT_HEADER_REMEMBERED_MASK_FOR_CLEAR 0xF0 /* OBJECT_HEADER_AGE_MASK */
#define J9_OBJECT_HEADER_REMEMBERED_MASK_FOR_TEST 0xF0 /* OBJECT_HEADER_AGE_MASK */
#define J9_OBJECT_HEADER_INDEXABLE 0x400 /* OBJECT_HEADER_INDEXABLE_NHS */
#define J9_OBJECT_HEADER_STACK_ALLOCATED 0x800 /* OBJECT_HEADER_STACK_ALLOCATED */

#define J9_STARTPC_NOT_TRANSLATED 0x1
#define J9_STARTPC_JNI_NATIVE 0x1
#define J9_STARTPC_METHOD_BREAKPOINTED 0x2
#define J9_STARTPC_NATIVE_REQUIRES_SWITCHING 0x2
#define J9_STARTPC_METHOD_IS_OVERRIDDEN 0x4
#define J9_STARTPC_DLT_READY 0x8
#define J9_STARTPC_STATUS 0xF

#define J9_STACKWALK_STOP_ITERATING 0x0
#define J9_STACKWALK_RC_NONE 0x0
#define J9_STACKWALK_ERROR_MODE_FATAL_EXIT 0x0
#define J9_STACKWALK_ERROR_MODE_IGNORE 0x1
#define J9_STACKWALK_KEEP_ITERATING 0x1
#define J9_STACKWALK_RECORD_BYTECODE_PC_OFFSET 0x1
#define J9_STACKWALK_RC_NO_MEMORY 0x1
#define J9_STACKWALK_DO_NOT_SNIFF_AND_WHACK 0x2
#define J9_STACKWALK_RC_FRAME_NOT_FOUND 0x2
#define J9_STACKWALK_RC_BAD_STATE_BUFFER 0x3
#define J9_STACKWALK_RC_STACK_CORRUPT 0x4
#define J9_STACKWALK_ITERATE_METHOD_CLASS_SLOTS 0x4
#define J9_STACKWALK_CHECK_I_SLOTS_FOR_OBJECTS 0x8
#define J9_STACKWALK_RESUME 0x10
#define J9_STACKWALK_CACHE_PCS 0x100
#define J9_STACKWALK_CACHE_CPS 0x200
#define J9_STACKWALK_CACHE_METHODS 0x400
#define J9_STACKWALK_CACHE_MASK 0x700
#define J9_STACKWALK_INCLUDE_ARRAYLET_LEAVES 0x10000
#define J9_STACKWALK_LINEAR 0x20000
#define J9_STACKWALK_VISIBLE_ONLY 0x40000
#define J9_STACKWALK_INCLUDE_NATIVES 0x80000
#define J9_STACKWALK_COUNT_SPECIFIED 0x100000
#define J9_STACKWALK_ITERATE_FRAMES 0x200000
#define J9_STACKWALK_ITERATE_O_SLOTS 0x400000
#define J9_STACKWALK_CACHE_ALLOCATED 0x800000
#define J9_STACKWALK_START_AT_JIT_FRAME 0x1000000
#define J9_STACKWALK_SAVE_STACKED_REGISTERS 0x2000000
#define J9_STACKWALK_SKIP_INLINES 0x4000000
#define J9_STACKWALK_HIDE_EXCEPTION_FRAMES 0x8000000
#define J9_STACKWALK_WALK_TRANSLATE_PC 0x10000000
#define J9_STACKWALK_MAINTAIN_REGISTER_MAP 0x20000000
#define J9_STACKWALK_ITERATE_HIDDEN_JIT_FRAMES 0x40000000
#define J9_STACKWALK_INCLUDE_CALL_IN_FRAMES 0x80000000

#define J9_FINDCLASS_FLAG_THROW_ON_FAIL 0x1
#define J9_FINDCLASS_FLAG_NO_DEBUG_EVENTS 0x2
#define J9_FINDCLASS_FLAG_EXISTING_ONLY 0x4
#define J9_FINDCLASS_FLAG_USE_LOADER_CP_ENTRIES 0x8
#define J9_FINDCLASS_FLAG_UNSAFE 0x10
#define J9_FINDCLASS_FLAG_NO_SUBCLASS_LINK 0x20
#define J9_FINDCLASS_FLAG_CHECK_PKG_ACCESS 0x80
#define J9_FINDCLASS_FLAG_RETRANSFORMING 0x100
#define J9_FINDCLASS_FLAG_FAST_HCR 0x200
#define J9_FINDCLASS_FLAG_REDEFINING 0x400
#define J9_FINDCLASS_FLAG_SHRC_ROMCLASS_EXISTS 0x800
#define J9_FINDCLASS_FLAG_NO_CHECK_FOR_EXISTING_CLASS 0x1000
#define J9_FINDCLASS_FLAG_NO_ISOLATION 0x2000
#define J9_FINDCLASS_FLAG_ANON 0x4000
#define J9_FINDCLASS_FLAG_FIND_MODULE_ON_FAIL 0x8000
/*
 * The class name supplied by the caller is invalid. If the class is not exempt
 * (see J9ClassIsExemptFromValidation), a NoClassDefFoundError will be thrown.
 */
#define J9_FINDCLASS_FLAG_NAME_IS_INVALID 0x10000
#define J9_FINDCLASS_FLAG_HIDDEN 0x20000
#define J9_FINDCLASS_FLAG_CLASS_OPTION_NESTMATE 0x40000
#define J9_FINDCLASS_FLAG_CLASS_OPTION_STRONG 0x80000

#define J9_FINDKNOWNCLASS_FLAG_INITIALIZE 0x1
#define J9_FINDKNOWNCLASS_FLAG_EXISTING_ONLY 0x2
#define J9_FINDKNOWNCLASS_FLAG_NON_FATAL 0x4

/* TODO: COMBOSPEC: Remove J9_GC_ARRAYLET_LAYOUT* and fix DDR */
#define J9_GC_ARRAYLET_LAYOUT_DATA_IN_SPINE_BIT 0x0
#define J9_GC_ARRAYLET_LAYOUT_DISCONTIGUOUS_BIT 0x0
#define J9_GC_ARRAYLET_LAYOUT_MASK 0x0
#define J9_GC_ARRAYLET_MINIMUM_ALIGNMENT 0x800

#define J9_GC_ALLOCATION_TYPE_ILLEGAL OMR_GC_ALLOCATION_TYPE_ILLEGAL
#define J9_GC_ALLOCATION_TYPE_TLH OMR_GC_ALLOCATION_TYPE_TLH
#define J9_GC_ALLOCATION_TYPE_SEGREGATED OMR_GC_ALLOCATION_TYPE_SEGREGATED
#define J9_GC_ALLOCATION_TYPE_COUNT OMR_GC_ALLOCATION_TYPE_COUNT

#define J9_GC_WRITE_BARRIER_TYPE_ILLEGAL OMR_GC_WRITE_BARRIER_TYPE_ILLEGAL
#define J9_GC_WRITE_BARRIER_TYPE_NONE OMR_GC_WRITE_BARRIER_TYPE_NONE
#define J9_GC_WRITE_BARRIER_TYPE_ALWAYS OMR_GC_WRITE_BARRIER_TYPE_ALWAYS
#define J9_GC_WRITE_BARRIER_TYPE_OLDCHECK OMR_GC_WRITE_BARRIER_TYPE_OLDCHECK
#define J9_GC_WRITE_BARRIER_TYPE_CARDMARK OMR_GC_WRITE_BARRIER_TYPE_CARDMARK
#define J9_GC_WRITE_BARRIER_TYPE_CARDMARK_INCREMENTAL OMR_GC_WRITE_BARRIER_TYPE_CARDMARK_INCREMENTAL
#define J9_GC_WRITE_BARRIER_TYPE_CARDMARK_AND_OLDCHECK OMR_GC_WRITE_BARRIER_TYPE_CARDMARK_AND_OLDCHECK
#define J9_GC_WRITE_BARRIER_TYPE_REALTIME OMR_GC_WRITE_BARRIER_TYPE_SATB
#define J9_GC_WRITE_BARRIER_TYPE_COUNT OMR_GC_WRITE_BARRIER_TYPE_COUNT

#define J9_GC_READ_BARRIER_TYPE_ILLEGAL OMR_GC_READ_BARRIER_TYPE_ILLEGAL
#define J9_GC_READ_BARRIER_TYPE_NONE OMR_GC_READ_BARRIER_TYPE_NONE
#define J9_GC_READ_BARRIER_TYPE_RANGE_CHECK OMR_GC_READ_BARRIER_TYPE_RANGE_CHECK
#define J9_GC_READ_BARRIER_TYPE_REGION_CHECK OMR_GC_READ_BARRIER_TYPE_REGION_CHECK
#define J9_GC_READ_BARRIER_TYPE_ALWAYS OMR_GC_READ_BARRIER_TYPE_ALWAYS

#define J9_GC_POLICY_ILLEGAL OMR_GC_POLICY_ILLEGAL
#define J9_GC_POLICY_OPTTHRUPUT OMR_GC_POLICY_OPTTHRUPUT
#define J9_GC_POLICY_OPTAVGPAUSE OMR_GC_POLICY_OPTAVGPAUSE
#define J9_GC_POLICY_GENCON OMR_GC_POLICY_GENCON
#define J9_GC_POLICY_BALANCED OMR_GC_POLICY_BALANCED
#define J9_GC_POLICY_METRONOME OMR_GC_POLICY_METRONOME
#define J9_GC_POLICY_NOGC OMR_GC_POLICY_NOGC

#define J9_GC_MINIMUM_OBJECT_SIZE 0x10
#if defined(J9VM_ENV_DATA64)
#define J9_GC_MARK_MAP_LOG_SIZEOF_UDATA 0x6
#define J9_GC_MARK_MAP_UDATA_MASK 0x3F
#else /* J9VM_ENV_DATA64 */
#define J9_GC_MARK_MAP_LOG_SIZEOF_UDATA 0x5
#define J9_GC_MARK_MAP_UDATA_MASK 0x1F
#endif /* J9VM_ENV_DATA64 */

#define J9VMGC_SIZECLASSES_MIN 0x1
#define J9VMGC_SIZECLASSES_MIN_SMALL 0x1
#define J9VMGC_SIZECLASSES_LOG_SMALLEST 0x4
#define J9VMGC_SIZECLASSES_LOG_LARGEST 0x10
#define J9VMGC_SIZECLASSES_MAX_SMALL 0x3F
#define J9VMGC_SIZECLASSES_NUM_SMALL 0x3F
#define J9VMGC_SIZECLASSES_ARRAYLET 0x40
#define J9VMGC_SIZECLASSES_LARGE 0x41
#define J9VMGC_SIZECLASSES_SINGLE_FREE 0x42
#define J9VMGC_SIZECLASSES_MAX 0x43
#define J9VMGC_SIZECLASSES_MULTI_FREE 0x43
#define J9VMGC_SIZECLASSES_MAX_SMALL_SLOT_COUNT 0x4000
#define J9VMGC_SIZECLASSES_MAX_SMALL_SIZE_BYTES 0x10000

#define J9_EXCEPT_SEARCH_NO_UNWIND 0x1
#define J9_EXCEPT_SEARCH_JAVA_HANDLER 0x1
#define J9_EXCEPT_SEARCH_JNI_HANDLER 0x2
#define J9_EXCEPT_SEARCH_JIT_HANDLER 0x3
#define J9_EXCEPT_SEARCH_NO_HANDLER 0x4

#define J9_VERIFY_SKIP_BOOTSTRAP_CLASSES 0x1
#define J9_VERIFY_OPTIMIZE 0x2
#define J9_VERIFY_EXCLUDE_ATTRIBUTE 0x4
#define J9_VERIFY_IGNORE_STACK_MAPS 0x8
#define J9_VERIFY_NO_FALLBACK 0x10
#define J9_VERIFY_BOOTCLASSPATH_STATIC 0x20
#define J9_VERIFY_VERBOSE_VERIFICATION 0x40
#define J9_VERIFY_DO_PROTECTED_ACCESS_CHECK 0x80
#define J9_VERIFY_ERROR_DETAILS 0x100

#define BCV_SUCCESS 0
#define BCV_FAIL 1
#define BCV_NOT_FOUND -1

/* TODO: Given that BCV_NOT_FOUND (-1) and BCV_ERR_INTERNAL_ERROR (-1) coexist in the existing code,
 * the conflict between BCV_NOT_FOUND and BCV_ERR_INTERNAL_ERROR will be addressed later in task 88899.
 */
#define BCV_ERR_INTERNAL_ERROR							-1
#define BCV_ERR_INSUFFICIENT_MEMORY						-2

#define BCV_ERR_FRAMES_INCOMPATIBLE_TYPE				-3
#define BCV_ERR_INCOMPATIBLE_TYPE						-4
#define BCV_ERR_STACK_SIZE_MISMATCH						-5
#define BCV_ERR_STACK_UNDERFLOW							-6
#define BCV_ERR_STACK_OVERFLOW							-7
#define BCV_ERR_JSR_STACK_UNDERFLOW						-8
#define BCV_ERR_JSR_STACK_OVERFLOW						-9
#define BCV_ERR_JSR_RET_ADDRESS_ON_STACK				-10
#define BCV_ERR_JSR_ILLEGAL_LOAD_OPERATION				-11
#define BCV_ERR_STACKMAP_FRAME_STACK_OVERFLOW			-12
#define BCV_ERR_STACKMAP_FRAME_LOCALS_UNDERFLOW			-13
#define BCV_ERR_STACKMAP_FRAME_LOCALS_OVERFLOW			-14
#define BCV_ERR_INIT_NOT_CALL_INIT						-15
#define BCV_ERR_WRONG_RETURN_TYPE						-16
#define BCV_ERR_INVALID_ARRAY_REFERENCE                 -17
#define BCV_ERR_CLASS_RELATIONSHIP_RECORD_REQUIRED		-18
#define BCV_ERR_UNUSED_19							-19
#define BCV_ERR_WRONG_TOP_TYPE							-20
#define BCV_ERR_EXPECT_STACKMAP_FRAME					-21
#define BCV_ERR_WRONG_STACKMAP_FRAME					-22
#define BCV_ERR_NO_STACKMAP_FRAME						-23
#define BCV_ERR_DEAD_CODE								-24
#define BCV_ERR_ARGUMENTS_MISMATCH						-25
#define BCV_ERR_BAD_ACCESS_PROTECTED					-26
#define BCV_ERR_BAD_INVOKESPECIAL						-27
#define BCV_ERR_BAD_INIT_OBJECT							-28
#define BCV_ERR_ARRAY_ARITY_OVERFLOW					-29
#define BCV_ERR_ARRAY_DIMENSION_MISMATCH				-30
#define BCV_ERR_BAD_BYTECODE							-31
#define BCV_ERR_UNEXPECTED_EOF							-32
#define BCV_ERR_INACCESSIBLE_CLASS						-33
#define BCV_ERR_BYTECODE_ERROR							-34
#define BCV_ERR_NEW_OJBECT_MISMATCH						-35

#define J9_GC_OBJ_HEAP_HOLE 0x1
#define J9_GC_MULTI_SLOT_HOLE 0x1
#define J9_GC_SINGLE_SLOT_HOLE 0x3
#define J9_GC_OBJ_HEAP_HOLE_MASK 0x3
#define J9_GC_SINGLE_SLOT_DAA_HOLE UDATA_MAX

#define J9_GC_COLLECT_REF_SOFT 0x0
#define J9_GC_COLLECT_REF_WEAK 0x1
#define J9_GC_COLLECT_REF_PHANTOM 0x2

#define J9_LOOK_ALLOW_FWD 0x1
#define J9_LOOK_INTERFACE 0x2
#define J9_LOOK_STATIC 0x4
#define J9_LOOK_NEW_INSTANCE 0x8
#define J9_LOOK_VIRTUAL 0x10
#define J9_LOOK_NO_CLIMB 0x20
#define J9_LOOK_NO_INTERFACE 0x40
#define J9_LOOK_CLCONSTRAINTS 0x80
#define J9_LOOK_NO_VISIBILITY_CHECK 0x100
#define J9_LOOK_IGNORE_INCOMPATIBLE_METHODS 0x200
#define J9_LOOK_JNI 0x400
#define J9_LOOK_NO_THROW 0x2000
#define J9_LOOK_DIRECT_NAS 0x4000
#define J9_LOOK_PARTIAL_SIGNATURE 0x8000
#define J9_LOOK_NO_JLOBJECT 0x10000
#define J9_LOOK_REFLECT_CALL 0x20000
#define J9_LOOK_HANDLE_DEFAULT_METHOD_CONFLICTS 0x40000
#define J9_LOOK_NO_JAVA 0x80000
#define J9_LOOK_NO_NESTMATES 0x100000
#define J9_LOOK_NO_MODULE_CHECKS 0x200000

#define J9_STR_NONE 0x0
#define J9_STR_XLAT 0x1
#define J9_STR_TENURE 0x2
#define J9_STR_INSTRUMENTABLE 0x4
#define J9_STR_INTERN 0x8
#define J9_STR_UNICODE 0x10
#define J9_STR_ANON_CLASS_NAME 0x20
/* Determines whether a copied string result will be null terminated */
#define J9_STR_NULL_TERMINATE_RESULT 0x40
/* Determines whether the string contains only ASCII characters (ord <= 127) */
#define J9_STR_ASCII 0x80

#define J9_JCL_FLAG_REFERENCE_OBJECTS 0x1
#define J9_JCL_FLAG_FINALIZATION 0x2
#define J9_JCL_FLAG_THREADGROUPS 0x8
/* #define J9_JCL_FLAG_UNUSED_10 0x10 */
#define J9_JCL_FLAG_COM_SUN_MANAGEMENT_PROP 0x20
#define J9_JCL_FLAG_JDK_MODULE_PATCH_PROP	0x40

#define J9_SIG_NO_SIG_QUIT 0x1
#define J9_SIG_NO_SIG_ABRT 0x2
#define J9_SIG_NO_SIG_CHAIN 0x4
#define J9_SIG_NO_SIG_INT 0x8
#define J9_SIG_XRS_SYNC 0x10
#define J9_SIG_XRS_ASYNC 0x20
#define J9_SIG_ZOS_CEEHDLR 0x40
#define J9_SIG_PERCOLATE_CONDITIONS 0x100
#define J9_SIG_POSIX_COOPERATIVE_SHUTDOWN 0x200

#define J9_THREAD_START_NO_ERROR 0x0
#define J9_THREAD_START_FAILED_VMTHREAD_ALLOC 0x1
#define J9_THREAD_START_FAILED_OOM_ALLOCATION 0x2
#define J9_THREAD_START_FAILED_LOCK_OBJECT_ALLOCATION 0x3
#define J9_THREAD_START_FAILED_TO_FORK_THREAD 0x4
#define J9_THREAD_START_UNSPECIFIED_ERROR 0x5
#define J9_THREAD_START_THROW_CURRENT_EXCEPTION 0x6

#define J9_GC_ALLOCATE_OBJECT_NON_INSTRUMENTABLE OMR_GC_ALLOCATE_OBJECT_NON_INSTRUMENTABLE
#define J9_GC_ALLOCATE_OBJECT_INSTRUMENTABLE OMR_GC_ALLOCATE_OBJECT_INSTRUMENTABLE
#define J9_GC_ALLOCATE_OBJECT_TENURED OMR_GC_ALLOCATE_OBJECT_TENURED
#define J9_GC_ALLOCATE_OBJECT_HASHED OMR_GC_ALLOCATE_OBJECT_HASHED
#define J9_GC_ALLOCATE_OBJECT_NON_ZERO_TLH OMR_GC_ALLOCATE_OBJECT_NON_ZERO_TLH

#define J9_SLOT_VALIDATE_ERROR_NONE 0x0
#define J9_SLOT_VALIDATE_ERROR_NATIVE_METHOD 0x1
#define J9_SLOT_VALIDATE_ERROR_TYPE_MISMATCH 0x2
#define J9_SLOT_VALIDATE_ERROR_INVALID_SLOT 0x3
#define J9_SLOT_VALIDATE_ERROR_OUT_OF_MEMORY 0x4
#define J9_SLOT_VALIDATE_ERROR_LOCAL_MAP_MISMATCH 0x5
#define J9_SLOT_VALIDATE_ERROR_LOCAL_MAP_ERROR 0x6

#define J9_NATIVE_TYPE_VOID 0x0
#define J9_NATIVE_TYPE_BOOLEAN 0x1
#define J9_NATIVE_TYPE_BYTE 0x2
#define J9_NATIVE_TYPE_CHAR 0x3
#define J9_NATIVE_TYPE_SHORT 0x4
#define J9_NATIVE_TYPE_FLOAT 0x5
#define J9_NATIVE_TYPE_INT 0x6
#define J9_NATIVE_TYPE_DOUBLE 0x7
#define J9_NATIVE_TYPE_LONG 0x8
#define J9_NATIVE_TYPE_OBJECT 0x9
#define J9_NATIVE_TYPE_CLASS 0xA

#define J9_NATIVE_LIBRARY_SWITCH_REQUIRED 0x1
#define J9_NATIVE_LIBRARY_SWITCH_JDBC 0x2

#define J9_METHOD_HANDLE_COMPILE_SHARED 0x0
#define J9_METHOD_HANDLE_COMPILE_CUSTOM 0x1
#define J9_METHOD_HANDLE_COMPILE_SYNC 0x2
#define J9_METHOD_HANDLE_INVOCATION_COMPILE_COUNT 0x1E

#define J9_METHOD_TYPE_ORIGIN_LDC 0x1
#define J9_METHOD_TYPE_ORIGIN_INVOKE_EXACT 0x2
#define J9_METHOD_TYPE_ORIGIN_INVOKE 0x4

#define J9_CHECK_ASYNC_NO_ACTION 0x0
#define J9_CHECK_ASYNC_THROW_EXCEPTION 0x1
#define J9_CHECK_ASYNC_POP_FRAMES 0x4

#define J9_BCLOOP_EXECUTE_BYTECODE 0x0
#define J9_BCLOOP_RUN_METHOD 0x1
#define J9_BCLOOP_SEND_TARGET_TAG 0x1
#define J9_BCLOOP_SEND_TARGET_SHIFT 0x1
#define J9_BCLOOP_JUMP_BYTECODE_PROTOTYPE 0x2
#define J9_BCLOOP_RUN_METHOD_COMPILED 0x3
#define J9_BCLOOP_RUN_EXCEPTION_HANDLER 0x4
#define J9_BCLOOP_RUN_JNI_NATIVE 0x5
#define J9_BCLOOP_STACK_OVERFLOW 0x6
#define J9_BCLOOP_RUN_METHOD_HANDLE 0x7
#define J9_BCLOOP_RUN_METHOD_HANDLE_COMPILED 0x8
#define J9_BCLOOP_RUN_METHOD_INTERPRETED 0x9
#define J9_BCLOOP_HANDLE_POP_FRAMES 0xA
#define J9_BCLOOP_J2I_TRANSITION 0xB
#define J9_BCLOOP_J2I_INVOKE_EXACT 0xC
#define J9_BCLOOP_J2I_VIRTUAL 0xD
#define J9_BCLOOP_LOAD_PRESERVED_AND_BRANCH 0xE
#define J9_BCLOOP_THROW_CURRENT_EXCEPTION 0xF
#define J9_BCLOOP_I2J_TRANSITION 0x10
#define J9_BCLOOP_RETURN_FROM_JIT 0x11
#define J9_BCLOOP_RETURN_FROM_JIT_CTOR 0x12
#define J9_BCLOOP_ENTER_METHOD_MONITOR 0x13
#define J9_BCLOOP_REPORT_METHOD_ENTER 0x14
#define J9_BCLOOP_CHECK_ASYNC 0x15
#define J9_BCLOOP_EXIT_INTERPRETER 0x16
#define J9_BCLOOP_FILL_OSR_BUFFER 0x17

/* Extended method block flags */
#define J9_RAS_METHOD_UNSEEN 0x0
#define J9_RAS_METHOD_SEEN 0x1
#define J9_RAS_METHOD_TRACING 0x2
#define J9_RAS_METHOD_TRACE_ARGS 0x4
#define J9_RAS_METHOD_TRIGGERING 0x8
#define J9_RAS_MASK 0xF
#define J9_SNAPSHOT_TRIGGER_ON_METHOD 0x10

#define J9_JNI_OFFLOAD_SWITCH_CREATE_JAVA_VM 0x1
#define J9_JNI_OFFLOAD_SWITCH_DEALLOCATE_VM_THREAD 0x2
#define J9_JNI_OFFLOAD_SWITCH_GET_ARRAY_ELEMENTS 0x3
#define J9_JNI_OFFLOAD_SWITCH_RELEASE_ARRAY_ELEMENTS 0x4
#define J9_JNI_OFFLOAD_SWITCH_GET_ARRAY_REGION 0x5
#define J9_JNI_OFFLOAD_SWITCH_SET_ARRAY_REGION 0x6
#define J9_JNI_OFFLOAD_SWITCH_GET_STRING_CHARS 0x7
#define J9_JNI_OFFLOAD_SWITCH_GET_STRING_REGION 0x8
#define J9_JNI_OFFLOAD_SWITCH_GET_STRING_UTF_CHARS 0x9
#define J9_JNI_OFFLOAD_SWITCH_GET_STRING_UTF_REGION 0xA
#define J9_JNI_OFFLOAD_SWITCH_NEW_STRING_UTF 0xB
#define J9_JNI_OFFLOAD_SWITCH_INTERPRETER 0xC
#define J9_JNI_OFFLOAD_SWITCH_FINALIZE_WORKER_THREAD 0xD
#define J9_JNI_OFFLOAD_SWITCH_GC_DISPATCHER_THREAD 0xE
#define J9_JNI_OFFLOAD_SWITCH_GC_HELPER_THREAD 0xF
#define J9_JNI_OFFLOAD_SWITCH_GC_MAIN_THREAD 0x10
#define J9_JNI_OFFLOAD_SWITCH_JIT_COMPILATION_THREAD 0x11
#define J9_JNI_OFFLOAD_SWITCH_JIT_SAMPLER_THREAD 0x12
#define J9_JNI_OFFLOAD_SWITCH_JIT_IPROFILER_THREAD 0x13
#define J9_JNI_OFFLOAD_SWITCH_JIT_HARDWARE_PROFILER_THREAD 0x14
#define J9_JNI_OFFLOAD_SWITCH_GC_FINALIZE_MAIN_THREAD 0x15
/* Jazz 99339: The reason code for JVMTI event callbacks on zOS.
 * Note: refer to jvmtiEventCallbacks (/runtime/include/jvmti.h) for reserved JVMTI events.
 */
#define J9_JNI_OFFLOAD_SWITCH_JVMTI_VM_INIT								0x16
#define J9_JNI_OFFLOAD_SWITCH_JVMTI_VM_DEATH							0x17
#define J9_JNI_OFFLOAD_SWITCH_JVMTI_THREAD_START						0x18
#define J9_JNI_OFFLOAD_SWITCH_JVMTI_THREAD_END							0x19
#define J9_JNI_OFFLOAD_SWITCH_JVMTI_CLASS_FILE_LOAD_HOOK				0x1A
#define J9_JNI_OFFLOAD_SWITCH_JVMTI_CLASS_LOAD							0x1B
#define J9_JNI_OFFLOAD_SWITCH_JVMTI_CLASS_PREPARE						0x1C
#define J9_JNI_OFFLOAD_SWITCH_JVMTI_VM_START							0x1D
#define J9_JNI_OFFLOAD_SWITCH_JVMTI_EXCEPTION							0x1E
#define J9_JNI_OFFLOAD_SWITCH_JVMTI_EXCEPTION_CATCH						0x1F
#define J9_JNI_OFFLOAD_SWITCH_JVMTI_SINGLE_STEP							0x20
#define J9_JNI_OFFLOAD_SWITCH_JVMTI_FRAME_POP							0x21
#define J9_JNI_OFFLOAD_SWITCH_JVMTI_BREAKPOINT							0x22
#define J9_JNI_OFFLOAD_SWITCH_JVMTI_FIELD_ACCESS						0x23
#define J9_JNI_OFFLOAD_SWITCH_JVMTI_FIELD_MODIFICATION					0x24
#define J9_JNI_OFFLOAD_SWITCH_JVMTI_METHOD_ENTRY						0x25
#define J9_JNI_OFFLOAD_SWITCH_JVMTI_METHOD_EXIT							0x26
#define J9_JNI_OFFLOAD_SWITCH_JVMTI_NATIVE_METHOD_BIND					0x27
#define J9_JNI_OFFLOAD_SWITCH_JVMTI_COMPILED_METHOD_LOAD				0x28
#define J9_JNI_OFFLOAD_SWITCH_JVMTI_COMPILED_METHOD_UNLOAD				0x29
#define J9_JNI_OFFLOAD_SWITCH_JVMTI_DYNAMIC_CODE_GENERATED				0x2A
#define J9_JNI_OFFLOAD_SWITCH_JVMTI_DATA_DUMP_REQUEST					0x2B
/* 0x2C Reserved for JVMTI event */
#define J9_JNI_OFFLOAD_SWITCH_JVMTI_MONITOR_WAIT						0x2D
#define J9_JNI_OFFLOAD_SWITCH_JVMTI_MONITOR_WAITED						0x2E
#define J9_JNI_OFFLOAD_SWITCH_JVMTI_MONITOR_CONTENDED_ENTER				0x2F
#define J9_JNI_OFFLOAD_SWITCH_JVMTI_MONITOR_CONTENDED_ENTERED			0x30
/* 0x31 Reserved for JVMTI event */
/* 0x32 Reserved for JVMTI event */
/* 0x33 Reserved for JVMTI event */
#define J9_JNI_OFFLOAD_SWITCH_JVMTI_RESOURCE_EXHAUSTED					0x34
#define J9_JNI_OFFLOAD_SWITCH_JVMTI_GC_START							0x35
#define J9_JNI_OFFLOAD_SWITCH_JVMTI_GC_FINISH							0x36
#define J9_JNI_OFFLOAD_SWITCH_JVMTI_OBJECT_FREE							0x37
#define J9_JNI_OFFLOAD_SWITCH_JVMTI_VM_OBJECT_ALLOC						0x38
/* 0x39 Reserved for JVMTI event */
#define J9_JNI_OFFLOAD_SWITCH_JVMTI_SAMPLED_OBJECT_ALLOC				0x3A
#define J9_JNI_OFFLOAD_SWITCH_J9JVMTI_COMPILING_START					0x3B
#define J9_JNI_OFFLOAD_SWITCH_J9JVMTI_COMPILING_END						0x3C
#define J9_JNI_OFFLOAD_SWITCH_J9JVMTI_INSTRUMENTABLE_OBJECT_ALLOC		0x3D
#define J9_JNI_OFFLOAD_SWITCH_J9JVMTI_VM_DUMP_START						0x3E
#define J9_JNI_OFFLOAD_SWITCH_J9JVMTI_VM_DUMP_END						0x3F
#define J9_JNI_OFFLOAD_SWITCH_J9JVMTI_GC_CYCLE_START					0x40
#define J9_JNI_OFFLOAD_SWITCH_J9JVMTI_GC_CYCLE_FINISH					0x41
#define J9_JNI_OFFLOAD_SWITCH_TRACE_SUBSCRIBER_THREAD					0x42

#define J9_JNI_OFFLOAD_SWITCH_THRESHOLD 0x4000

#define J9_SPLIT_TABLE_INDEX_MASK 0xFFFF
#define J9_STATIC_SPLIT_TABLE_INDEX_FLAG 0x10000
#define J9_SPECIAL_SPLIT_TABLE_INDEX_FLAG 0x20000

#define J9_SSF_CO_REF_SLOT_CNT 0x10
#define J9_SSF_JNI_PUSHED_REF_COUNT_MASK 0xFF
#define J9_SSF_RETURNS_OBJECT 0x10000 /* J9_STACK_FLAGS_RETURNS_OBJECT */
#define J9_SSF_JNI_REFS_REDIRECTED 0x10000 /* J9_STACK_FLAGS_JNI_REFS_REDIRECTED */
#define J9_SSF_REL_VM_ACC 0x20000 /* J9_STACK_FLAGS_RELEASE_VMACCESS */
#define J9_SSF_CALL_OUT_FRAME_ALLOC 0x20000 /* J9_STACK_FLAGS_CALL_OUT_FRAME_ALLOCATED */
#define J9_SSF_JIT_JNI_FRAME_COLLAPSE_BITS 0x30000 /* J9_SSF_CALL_OUT_FRAME_ALLOC | J9_SSF_JNI_REFS_REDIRECTED */
#define J9_SSF_EXIT_TRC_L3 0x40000 /* J9_STACK_FLAGS_EXIT_TRACEPOINT_LEVEL3 */
#define J9_SSF_USE_SPEC_CL 0x40000 /* J9_STACK_FLAGS_USE_SPECIFIED_CLASS_LOADER */
#define J9_SSF_JIT_RESOLVE 0x80000 /* J9_STACK_FLAGS_JIT_RESOLVE_FRAME */
#define J9_SSF_JIT_RESOLVE_STATIC_METHOD 0x180000 /* J9_STACK_FLAGS_JIT_RESOLVE_FRAME | J9_STACK_FLAGS_JIT_STATIC_METHOD_RESOLVE */
#define J9_SSF_JIT_RESOLVE_SPECIAL_METHOD 0x280000 /* J9_STACK_FLAGS_JIT_RESOLVE_FRAME | J9_STACK_FLAGS_JIT_SPECIAL_METHOD_RESOLVE */
#define J9_SSF_JIT_RESOLVE_DATA 0x380000 /* J9_STACK_FLAGS_JIT_RESOLVE_FRAME | J9_STACK_FLAGS_JIT_DATA_RESOLVE */
#define J9_SSF_JIT_RESOLVE_INTERFACE_LOOKUP 0x480000 /* J9_STACK_FLAGS_JIT_RESOLVE_FRAME | J9_STACK_FLAGS_JIT_LOOKUP_RESOLVE */
#define J9_SSF_JIT_RESOLVE_VIRTUAL_METHOD 0x580000 /* J9_STACK_FLAGS_JIT_RESOLVE_FRAME | J9_STACK_FLAGS_JIT_VIRTUAL_METHOD_RESOLVE */
#define J9_SSF_JIT_RESOLVE_INTERFACE_METHOD 0x680000 /* J9_STACK_FLAGS_JIT_RESOLVE_FRAME | J9_STACK_FLAGS_JIT_INTERFACE_METHOD_RESOLVE */
#define J9_SSF_JIT_RESOLVE_RUNTIME_HELPER 0x880000 /* J9_STACK_FLAGS_JIT_RESOLVE_FRAME | J9_STACK_FLAGS_JIT_RUNTIME_HELPER_RESOLVE */
#define J9_SSF_JIT_RESOLVE_RECOMPILATION 0x980000 /* J9_STACK_FLAGS_JIT_RESOLVE_FRAME | J9_STACK_FLAGS_JIT_RECOMPILATION_RESOLVE */
#define J9_SSF_JIT_RESOLVE_MON_ENT 0xA80000 /* J9_STACK_FLAGS_JIT_RESOLVE_FRAME | J9_STACK_FLAGS_JIT_MONITOR_ENTER_RESOLVE */
#define J9_SSF_JIT_RESOLVE_ALLOCATION 0xB80000 /* J9_STACK_FLAGS_JIT_RESOLVE_FRAME | J9_STACK_FLAGS_JIT_ALLOCATION_RESOLVE */
#define J9_SSF_JIT_RESOLVE_BEFORE_ANEWARRAY 0xC80000 /* J9_STACK_FLAGS_JIT_RESOLVE_FRAME | J9_STACK_FLAGS_JIT_BEFORE_ANEWARRAY_RESOLVE */
#define J9_SSF_JIT_RESOLVE_BEFORE_MULTIANEWARRAY 0xD80000 /* J9_STACK_FLAGS_JIT_RESOLVE_FRAME | J9_STACK_FLAGS_JIT_BEFORE_MULTIANEWARRAY_RESOLVE */
#define J9_SSF_JIT_RESOLVE_INDUCE_OSR 0xE80000 /* J9_STACK_FLAGS_JIT_RESOLVE_FRAME | J9_STACK_FLAGS_JIT_INDUCE_OSR_RESOLVE */
#define J9_SSF_METHOD_ENTRY 0x8000000 /* J9_STACK_FLAGS_METHOD_ENTRY */
#define J9_SSF_JIT_CALLIN 0x10000000 /* J9_STACK_FLAGS_JIT_CALL_IN_FRAME */
#define J9_SSF_JIT_CALLIN_METHODTYPE 0x10100000 /* J9_SSF_JIT_CALLIN | J9_STACK_FLAGS_JIT_CALL_IN_TYPE_METHODTYPE */
#define J9_SSF_JIT_JNI_CALLOUT 0x20000000 /* J9_STACK_FLAGS_JIT_JNI_CALL_OUT_FRAME */
#define J9_SSF_JIT_NATIVE_TRANSITION_FRAME 0x40000000 /* J9_STACK_FLAGS_JIT_NATIVE_TRANSITION */
#define J9_SSF_JIT_RESOLVE_STACK_OVERFLOW 0x00780000 /* J9_STACK_FLAGS_JIT_RESOLVE_FRAME | J9_STACK_FLAGS_JIT_STACK_OVERFLOW_RESOLVE_FRAME */

#define J9_XACCESS_NONE 0
#define J9_XACCESS_PENDING 1
#define J9_XACCESS_EXCLUSIVE 2
#define J9_XACCESS_HANDING_OFF 3
#define J9_XACCESS_HANDED_OFF 4
#define J9_XACCESS_HANDING_OFF_FROM_EXTERNAL_THREAD 5

#define J9_IDLE_TUNING_GC_ON_IDLE 0x1
#define J9_IDLE_TUNING_COMPACT_ON_IDLE 0x2
#define J9_IDLE_TUNING_IGNORE_UNRECOGNIZED_OPTIONS 0x4

#define J9_CLASSLOADER_TYPE_OTHERS		0
#define J9_CLASSLOADER_TYPE_BOOT		1
#define J9_CLASSLOADER_TYPE_PLATFORM	2

/* Flag for Nestmates invokeVirtual on private methods */
#define J9_VTABLE_INDEX_DIRECT_METHOD_FLAG 0x1

/* Tag bits for J9RAMInterfaceMethodRef->methodIndexAndArgCount:
 *
 *	J9_ITABLE_INDEX_METHOD_INDEX - index represents a direct method index
 *	J9_ITABLE_INDEX_OBJECT       - use Object rather than the targetted interfaceClass
 *
 * Private methods in interface will have only J9_ITABLE_INDEX_METHOD_INDEX set, indicating that
 * the underlying index is a method index into the interfaceClass of the ref.
 *
 * vTable methods in Object will have only J9_ITABLE_INDEX_OBJECT set, indicating that
 * the underlying index is a vTable offset in Object.
 *
 * Non-vTable methods in Object will have J9_ITABLE_INDEX_OBJECT and J9_ITABLE_INDEX_METHOD_INDEX set,
 * indicating that the underlying index is a method index in Object.
 *
 * J9_ITABLE_INDEX_UNRESOLVED represents an impossible value to represent an unresolved
 * CP entry (an unaligned vTable offset). J9_ITABLE_INDEX_UNRESOLVED_VALUE is the index value
 * after the CP value has been downshifted.
 */
#define J9_ITABLE_INDEX_SHIFT 10
#define J9_ITABLE_INDEX_METHOD_INDEX ((UDATA)1 << 8)
#define J9_ITABLE_INDEX_OBJECT ((UDATA)1 << 9)
#define J9_ITABLE_INDEX_TAG_BITS (J9_ITABLE_INDEX_METHOD_INDEX | J9_ITABLE_INDEX_OBJECT)
#define J9_ITABLE_INDEX_UNRESOLVED_VALUE ((UDATA)1)
#define J9_ITABLE_INDEX_UNRESOLVED ((J9_ITABLE_INDEX_UNRESOLVED_VALUE << J9_ITABLE_INDEX_SHIFT) | J9_ITABLE_INDEX_OBJECT)

/* Tag bits for iTableOffset field in JIT interface snippet data:
 *
 *	J9_ITABLE_OFFSET_DIRECT  - offset field is actually a direct J9Method*
 *	J9_ITABLE_OFFSET_VIRTUAL - offset field represents a vTable offset, not iTable
 */
#define J9_ITABLE_OFFSET_DIRECT 1
#define J9_ITABLE_OFFSET_VIRTUAL 2
#define J9_ITABLE_OFFSET_TAG_BITS (J9_ITABLE_OFFSET_DIRECT | J9_ITABLE_OFFSET_VIRTUAL)

/*
 * These constants are declared only so that they are available in core files to retain
 * compatibility with old DTFJ plugins, see https://github.com/eclipse/openj9/issues/6316.
 *
 * They should not be used for any other purpose.
 */
#define J9_JAVA_CLASS_ARRAY 0x10000
#define J9_JAVA_CLASS_DEPTH_MASK 0xFFFF
#define J9_JAVA_CLASS_DYING 0x8000000
#define J9_JAVA_CLASS_GC_SPECIAL 0x800000
#define J9_JAVA_CLASS_HOT_SWAPPED_OUT 0x4000000
#define J9_JAVA_CLASS_RAM_ARRAY 0x10000
#define J9_JAVA_CLASS_RAM_SHAPE_SHIFT 0x10
#define J9_JAVA_CLASS_REFERENCE_MASK 0x30000000
#define J9_JAVA_INTERFACE 0x200
#define J9_JAVA_NATIVE 0x100
#define J9_JAVA_STATIC 0x8

#ifdef __cplusplus
}
#endif

#endif /* J9CONSTS_H */
