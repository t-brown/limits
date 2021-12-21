/*
 * BSD 3-Clause License
 *
 * Copyright (c) 2021, Timothy Brown
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include <stdlib.h>
#include <stdio.h>
#include <sys/resource.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifdef HAVE_MPI
#include <mpi.h>
#endif

int
plimit(char *limit)
{

	int rank = 0;
	int world = 0;
	int resource = 0;
	struct rlimit lim = {0};

#ifdef HAVE_MPI

	MPI_Comm_size(MPI_COMM_WORLD, &world);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
#endif
	if (strcmp(limit, "core") == 0) {
		resource = RLIMIT_CORE;
	} else if (strcmp(limit, "cpu") == 0) {
		resource = RLIMIT_CPU;
	} else if (strcmp(limit, "data") == 0) {
		resource = RLIMIT_DATA;
	} else if (strcmp(limit, "fsize") == 0) {
		resource = RLIMIT_FSIZE;
	} else if (strcmp(limit, "memlock") == 0) {
		resource = RLIMIT_MEMLOCK;
	} else if (strcmp(limit, "nofile") == 0) {
		resource = RLIMIT_NOFILE;
	} else if (strcmp(limit, "nproc") == 0) {
		resource = RLIMIT_NPROC;
	} else if (strcmp(limit, "rss") == 0) {
		resource = RLIMIT_RSS;
	} else if (strcmp(limit, "stack") == 0) {
		resource = RLIMIT_STACK;
	}

	if (getrlimit(resource, &lim) == 0) {
		printf("[%03d/%03d] %s limits -> soft: %ju\thard: %ju\n",
		       rank, world, limit, (uintmax_t)lim.rlim_cur,
		       (uintmax_t)lim.rlim_max);
	} else {
		fprintf(stderr, "unable to get %s from getrlimit(): %s\n", limit,
			strerror(errno));
	}

	return EXIT_SUCCESS;
}

