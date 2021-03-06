myhalf FragmentSoftness(float Depth, sampler2D DepthTexture, const vec2 ScreenCoord, const ivec4 Viewport, const float ZNear, const float ZFar, myhalf Scale)
{
	vec2 tc = ScreenCoord / vec2(Viewport.zw);

	myhalf fragdepth = ZNear*ZFar/(ZFar - texture2D(DepthTexture, tc).r*(ZFar-ZNear));
	myhalf partdepth = Depth;
	
	myhalf d = max((fragdepth - partdepth) * Scale, 0.0);
	myhalf softness = 1.0 - min(1.0, d);
	
	softness *= softness;
	softness = 1.0 - softness * softness;
	return softness;
}
