/*
 * Cryptographic API.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 *
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/crypto.h>
#include <linux/vmalloc.h>
#include <linux/mm.h>
#include <linux/lzo.h>
<<<<<<< HEAD
#include <crypto/internal/scompress.h>
=======
>>>>>>> FETCH_HEAD

struct lzo_ctx {
	void *lzo_comp_mem;
};

<<<<<<< HEAD
static void *lzo_alloc_ctx(struct crypto_scomp *tfm)
{
	void *ctx;

	ctx = kmalloc(LZO1X_MEM_COMPRESS, GFP_KERNEL | __GFP_NOWARN);
	if (!ctx)
		ctx = vmalloc(LZO1X_MEM_COMPRESS);
	if (!ctx)
		return ERR_PTR(-ENOMEM);

	return ctx;
}

=======
>>>>>>> FETCH_HEAD
static int lzo_init(struct crypto_tfm *tfm)
{
	struct lzo_ctx *ctx = crypto_tfm_ctx(tfm);

<<<<<<< HEAD
	ctx->lzo_comp_mem = lzo_alloc_ctx(NULL);
	if (IS_ERR(ctx->lzo_comp_mem))
=======
	ctx->lzo_comp_mem = kmalloc(LZO1X_MEM_COMPRESS,
				    GFP_KERNEL | __GFP_NOWARN);
	if (!ctx->lzo_comp_mem)
		ctx->lzo_comp_mem = vmalloc(LZO1X_MEM_COMPRESS);
	if (!ctx->lzo_comp_mem)
>>>>>>> FETCH_HEAD
		return -ENOMEM;

	return 0;
}

<<<<<<< HEAD
static void lzo_free_ctx(struct crypto_scomp *tfm, void *ctx)
{
	kvfree(ctx);
}

=======
>>>>>>> FETCH_HEAD
static void lzo_exit(struct crypto_tfm *tfm)
{
	struct lzo_ctx *ctx = crypto_tfm_ctx(tfm);

<<<<<<< HEAD
	lzo_free_ctx(NULL, ctx->lzo_comp_mem);
}

static int __lzo_compress(const u8 *src, unsigned int slen,
			  u8 *dst, unsigned int *dlen, void *ctx)
{
	size_t tmp_len = *dlen; /* size_t(ulong) <-> uint on 64 bit */
	int err;

	err = lzo1x_1_compress(src, slen, dst, &tmp_len, ctx);
=======
	kvfree(ctx->lzo_comp_mem);
}

static int lzo_compress(struct crypto_tfm *tfm, const u8 *src,
			    unsigned int slen, u8 *dst, unsigned int *dlen)
{
	struct lzo_ctx *ctx = crypto_tfm_ctx(tfm);
	size_t tmp_len = *dlen; /* size_t(ulong) <-> uint on 64 bit */
	int err;

	err = lzo1x_1_compress(src, slen, dst, &tmp_len, ctx->lzo_comp_mem);
>>>>>>> FETCH_HEAD

	if (err != LZO_E_OK)
		return -EINVAL;

	*dlen = tmp_len;
	return 0;
}

<<<<<<< HEAD
static int lzo_compress(struct crypto_tfm *tfm, const u8 *src,
			unsigned int slen, u8 *dst, unsigned int *dlen)
{
	struct lzo_ctx *ctx = crypto_tfm_ctx(tfm);

	return __lzo_compress(src, slen, dst, dlen, ctx->lzo_comp_mem);
}

static int lzo_scompress(struct crypto_scomp *tfm, const u8 *src,
			 unsigned int slen, u8 *dst, unsigned int *dlen,
			 void *ctx)
{
	return __lzo_compress(src, slen, dst, dlen, ctx);
}

static int __lzo_decompress(const u8 *src, unsigned int slen,
			    u8 *dst, unsigned int *dlen)
=======
static int lzo_decompress(struct crypto_tfm *tfm, const u8 *src,
			      unsigned int slen, u8 *dst, unsigned int *dlen)
>>>>>>> FETCH_HEAD
{
	int err;
	size_t tmp_len = *dlen; /* size_t(ulong) <-> uint on 64 bit */

	err = lzo1x_decompress_safe(src, slen, dst, &tmp_len);

	if (err != LZO_E_OK)
		return -EINVAL;

	*dlen = tmp_len;
	return 0;
<<<<<<< HEAD
}

static int lzo_decompress(struct crypto_tfm *tfm, const u8 *src,
			  unsigned int slen, u8 *dst, unsigned int *dlen)
{
	return __lzo_decompress(src, slen, dst, dlen);
}

static int lzo_sdecompress(struct crypto_scomp *tfm, const u8 *src,
			   unsigned int slen, u8 *dst, unsigned int *dlen,
			   void *ctx)
{
	return __lzo_decompress(src, slen, dst, dlen);
=======

>>>>>>> FETCH_HEAD
}

static struct crypto_alg alg = {
	.cra_name		= "lzo",
	.cra_flags		= CRYPTO_ALG_TYPE_COMPRESS,
	.cra_ctxsize		= sizeof(struct lzo_ctx),
	.cra_module		= THIS_MODULE,
	.cra_init		= lzo_init,
	.cra_exit		= lzo_exit,
	.cra_u			= { .compress = {
<<<<<<< HEAD
	.coa_compress		= lzo_compress,
	.coa_decompress		= lzo_decompress } }
};

static struct scomp_alg scomp = {
	.alloc_ctx		= lzo_alloc_ctx,
	.free_ctx		= lzo_free_ctx,
	.compress		= lzo_scompress,
	.decompress		= lzo_sdecompress,
	.base			= {
		.cra_name	= "lzo",
		.cra_driver_name = "lzo-scomp",
		.cra_module	 = THIS_MODULE,
	}
=======
	.coa_compress 		= lzo_compress,
	.coa_decompress  	= lzo_decompress } }
>>>>>>> FETCH_HEAD
};

static int __init lzo_mod_init(void)
{
<<<<<<< HEAD
	int ret;

	ret = crypto_register_alg(&alg);
	if (ret)
		return ret;

	ret = crypto_register_scomp(&scomp);
	if (ret) {
		crypto_unregister_alg(&alg);
		return ret;
	}

	return ret;
=======
	return crypto_register_alg(&alg);
>>>>>>> FETCH_HEAD
}

static void __exit lzo_mod_fini(void)
{
	crypto_unregister_alg(&alg);
<<<<<<< HEAD
	crypto_unregister_scomp(&scomp);
=======
>>>>>>> FETCH_HEAD
}

module_init(lzo_mod_init);
module_exit(lzo_mod_fini);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("LZO Compression Algorithm");
MODULE_ALIAS_CRYPTO("lzo");
